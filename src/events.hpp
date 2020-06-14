#pragma once

#include <SDL2/SDL.h>

class Events
{
	public:
		enum events {EVENTLESS, QUIT, PAUSE};

		Events();

		int get_event();

	private:
		SDL_Event _event;
};
