#pragma once

#include <SDL2/SDL.h>
class SDL_helper;

class Events
{
	public:
		enum events {EVENTLESS, QUIT, PAUSE};

		Events(SDL_helper&);

		int get_event();

	private:
		SDL_Event _event;
		SDL_helper& _sdl_helper;
};
