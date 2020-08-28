#include "events.hpp"
#include <iostream>
#include "sdl_helper.hpp"
using namespace std;

Events::Events(SDL_helper& sdl_h):
	_sdl_helper(sdl_h)
{
	_sdl_helper.check_null("SDL Event", SDL_Init(SDL_INIT_EVENTS));
}

const vector<int>& Events::get_events()
{
	_events.clear();

	while( SDL_PollEvent(&_event) != 0)
	{
		auto& e = _event;
		// presses key
		if( e.type == SDL_KEYDOWN )
		{
			 _events.push_back(e.key.keysym.sym);
		}
	}
	return _events;
}

SDL_KeyCode Events::get_key_codes()
{
	SDL_KeyCode kc;
	return kc;
}
