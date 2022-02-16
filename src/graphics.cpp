#include <SDL2/SDL.h>
#include <iostream>
#include "graphics.hpp"
#include <unistd.h>
#include <cstdint>
#include "texter.hpp"
#include "sdl_helper.hpp"
#include "hex/hex_grid.hpp"
using namespace std;

Graphics::Graphics(
		const std::string& window_name, 
		size_t x,
		size_t y,
		SDL_helper& sdl_h):
	_sdl_helper(sdl_h)
{
	_screen_width = x;
	_screen_height = y;
	auto pixel_format = SDL_PIXELFORMAT_RGBA8888;

	_sdl_helper.check_null("SDL initialization", SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS));

	// create window
	_window = SDL_CreateWindow(
			window_name.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 
			_screen_width,
			_screen_height,
			SDL_WINDOW_SHOWN); 
	_sdl_helper.check_null("SDL window", _window);

	// create viewports
	// _bar_view (on top to begin with)
	_bar_view.x = _bar_view.y = 0;
	_bar_view.w = _screen_width;
	_bar_view.h = 50; // hard coded

	_main_view.x = 0;
	_main_view.y = _bar_view.h;
	_main_view.w = _screen_width;
	_main_view.h = _screen_height - _bar_view.h;

	// create renderer
	_sdl_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	_sdl_helper.check_null("SDL renderer", _sdl_renderer);

	//Initialize renderer color
	SDL_SetRenderDrawColor( _sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

}

Graphics::~Graphics()
{
	SDL_DestroyRenderer(_sdl_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Graphics::clear_screen()
{
	SDL_SetRenderDrawColor( _sdl_renderer, 50, 50, 50, 255 );
	SDL_RenderClear(_sdl_renderer);
}

void Graphics::render()
{
	SDL_RenderPresent(_sdl_renderer);
}

void Graphics::draw(const Hex_grid& grid)
{
	draw_grid(grid);
}

void Graphics::draw(shared_ptr<Texter> texter)
{
	for(const Text& text : texter->get_texts())
	{
		set_viewport(static_cast<viewport>(text.view_port));
		SDL_RenderCopy(_sdl_renderer, text.texture, NULL, &text.size);
	}
}

void Graphics::set_viewport(viewport vp)
{
	switch(vp)
	{
		case(MAIN):
		default:
			SDL_RenderSetViewport(_sdl_renderer, &_main_view);
			break;
		case(BAR):
			SDL_RenderSetViewport(_sdl_renderer, &_bar_view);
			break;
		case(SIDE_BAR):
			SDL_RenderSetViewport(_sdl_renderer, &_side_bar_view);
			break;
	}
}

const SDL_Rect& Graphics::get_viewport(int vp)
{
	return get_viewport(static_cast<viewport>(vp));
}

const SDL_Rect& Graphics::get_viewport(viewport vp)
{
	switch(vp)
	{
		case(MAIN):
		default:
			return _main_view;
		case(BAR):
			return _bar_view;
		case(SIDE_BAR):
			return  _side_bar_view;
	}
}

// PRIVATE

void Graphics::draw_grid(const Hex_grid& grid)
{
	SDL_RenderSetViewport(_sdl_renderer, &_main_view);
	for(auto& tile : grid.get_grid())
	{
		const SDL_Point* p = &tile.get_corners().front();
		const SDL_Point* last_point = p + 5;
		const SDL_Color& c = tile.get_color();
		SDL_SetRenderDrawColor( _sdl_renderer, c.r, c.g, c.b, c.a);
		SDL_RenderDrawLines( _sdl_renderer, p, 6);
		SDL_RenderDrawLine( _sdl_renderer, last_point->x, last_point->y, p->x, p->y);
	}
}

//void Graphics::load_image(const std::string& path)
//{
	
