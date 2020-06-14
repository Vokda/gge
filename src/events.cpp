#include "events.hpp"
#include <iostream>
#include "sdl_init_helper.hpp"
using namespace std;

Events::Events()
{
	check_null("SDL Event", SDL_Init(SDL_INIT_EVENTS));
}

int Events::get_event()
{
	while( SDL_PollEvent(&_event) != 0)
	{
		auto& e = _event;
		if(e.type == SDL_QUIT)
		{
			return QUIT;
		}
		// presses key
		else if( e.type == SDL_KEYDOWN )
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				case SDLK_q:
					return QUIT;
					break;
				case SDLK_SPACE:
					return PAUSE;
			}
		}
	}
	return EVENTLESS;
}
