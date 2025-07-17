#include "events.hpp"
#include "gui.hpp"
using namespace std;

Events::Events(shared_ptr<gge::GUI> gui):
    GGE_module(EVENTS),
    _log(Logger::get_instance().add_category("Events")),
    _gui(gui)
{
    check_null("SDL Event", SDL_Init(SDL_INIT_EVENTS));
}

void Events::poll_events()
{
    //_events.clear();

    while( SDL_PollEvent(&_event) != 0)
    {
        // gui now works like in i3 (hovering = focus) see _gui's implementation for mor details
        if(_gui->process_event(_event))
        {
            break;
        }

        switch(_event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                //case SDL_MOUSEBUTTONUP:
                _events.push(_event.button.button);
                break;
            case SDL_KEYDOWN:
                _events.push(_event.key.keysym.sym);
                break;
        }
    }
}

const queue<int>& Events::get_events()
{
	return _events;
}

int Events::pop_event()
{
	if(_events.empty())
		return 0;
	else
	{
		int e = _events.front();
		_events.pop();
		return e;
	}
}

/*SDL_KeyCode Events::get_key_codes()
{
	SDL_KeyCode kc; 
	return kc;
}*/

vector<int> Events::get_mouse_position()
{
	int x, y;
	//Uint32 buttons;

	SDL_PumpEvents();  // make sure we have the latest mouse state.

	/*buttons =*/ SDL_GetMouseState(&x, &y);

/*#ifdef DEBUG
	SDL_Log("Mouse cursor is at %d, %d", x, y);
	if ((buttons & SDL_BUTTON_LMASK) != 0) {
		SDL_Log("Mouse Button 1 (left) is pressed.");
	}
#endif*/

	return vector<int>({x, y});
}
