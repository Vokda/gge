#include <SDL2/SDL.h>
#include <iostream>
#include "graphics.hpp"
#include <unistd.h>
#include <cstdint>
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
	SDL_SetRenderDrawColor( _sdl_renderer, 0, 0, 0, 255 );
	SDL_RenderClear(_sdl_renderer);
}

void Graphics::render()
{
	SDL_RenderPresent(_sdl_renderer);
}

void Graphics::draw_grid(const Hex_grid& grid)
{
	for(auto& tile : grid.get_grid())
	{
		const SDL_Point* p = &tile.get_corners().front();
		const SDL_Point* last_point = p + 5;
		SDL_SetRenderDrawColor( _sdl_renderer, 255, 255, 255, 255 );
		SDL_RenderDrawLines( _sdl_renderer, p, 6);
		SDL_RenderDrawLine( _sdl_renderer, last_point->x, last_point->y, p->x, p->y);
	}

}

//void Graphics::load_image(const std::string& path)
//{
	
