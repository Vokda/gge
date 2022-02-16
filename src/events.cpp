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
		switch(_event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
			//case SDL_MOUSEBUTTONUP:
				_events.push_back(_event.button.button);
				break;
			case SDL_KEYDOWN:
				_events.push_back(_event.key.keysym.sym);
				break;
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

/*#ifdef DEBUG
	SDL_Log("Mouse cursor is at %d, %d", x, y);
	if ((buttons & SDL_BUTTON_LMASK) != 0) {
		SDL_Log("Mouse Button 1 (left) is pressed.");
	}
#endif*/

	return vector<int>({x, y});
}
