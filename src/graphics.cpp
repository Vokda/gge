#include <SDL2/SDL.h>
#include <iostream>
#include "graphics.hpp"
#include <unistd.h>
#include <cstdint>
#include "sdl_init_helper.hpp"
#include "hex_grid.hpp"
using namespace std;

Graphics::Graphics(const std::string& window_name, size_t x, size_t y)
{
	_screen_width = x;
	_screen_height = y;
	auto pixel_format = SDL_PIXELFORMAT_RGBA8888;

	check_null("SDL initialization", SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS));

	// create window
	_window = SDL_CreateWindow(
			window_name.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 
			_screen_width,
			_screen_height,
			SDL_WINDOW_SHOWN); 
	check_null("SDL window", _window);

	// create renderer
	_sdl_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	check_null("SDL renderer", _sdl_renderer);

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
	// blue
	SDL_SetRenderDrawColor( _sdl_renderer, 135, 206, 235, 255 );
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
		SDL_RenderDrawLines( _sdl_renderer, p, 6);
	}
}
