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
		// presses mouse
		if( e.type == SDL_MOUSEBUTTONDOWN )
		{
			_events.push_back(-1);
		}
	}
	return _events;
}

SDL_KeyCode Events::get_key_codes()
{
	SDL_KeyCode kc;
	return kc;
}

vector<int> Events::get_mouse_position()
{
	int x, y;
	Uint32 buttons;

	SDL_PumpEvents();  // make sure we have the latest mouse state.

	buttons = SDL_GetMouseState(&x, &y);

#ifdef DEBUG
	SDL_Log("Mouse cursor is at %d, %d", x, y);
	if ((buttons & SDL_BUTTON_LMASK) != 0) {
		SDL_Log("Mouse Button 1 (left) is pressed.");
	}
#endif

	return vector<int>({x, y});
}
