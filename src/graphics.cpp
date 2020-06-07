#include <SDL2/SDL.h>
#include <iostream>
#include "graphics.hpp"
#include <unistd.h>
#include <cstdint>
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


void Graphics::render()
{
	// blue
	SDL_SetRenderDrawColor( _sdl_renderer, 135, 206, 235, 255 );
	SDL_RenderClear(_sdl_renderer);

	// do drawing

	SDL_RenderPresent(_sdl_renderer);
}



/*
 * check sdl return values
 * and handle it apropriately
 */
void Graphics::check_null(const std::string& check_name, const void * SDL_struct)
{
	cout << check_name;
	if(SDL_struct == nullptr)// or *(int*)(SDL_struct) < 0)
	{
		cerr << " - SDL Error: " << SDL_GetError() << endl;
		throw 1;
	}
	else
	{
		cout << " - OK" <<endl;
	}
}

void Graphics::check_null(const std::string& check_name, const int SDL_result)
{
	cout << check_name;
	if(SDL_result < 0)
	{
		cerr << " - SDL Error: " << SDL_GetError() << endl;
		throw 1;
	}
	else
	{
		cout << " - OK" <<endl;
	}
}

