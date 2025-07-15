#pragma once

#include "../logger.hpp"
#include <queue>
#include <SDL2/SDL.h>
#include "gge_module.hpp"
#include "../sdl_helper.hpp"
#include <memory>
using namespace std;
namespace gge
{
    class GUI;
}

enum device {KEYBOARD, MOUSE};

/*struct event TODO not in use? causes warings
{
	event()
	{
		type = 0;
		symbol = 0;
	}
	event(SDL_Event& e)
	{
		type = e.type;
		if(type == SDL_MOUSEBUTTONDOWN or type == SDL_MOUSEBUTTONUP) // ???
		{
			symbol = (unsigned int) e.button.button;
		}
		else if((bool)SDL_KEYDOWN or (bool)SDL_KEYUP)
		{
			symbol = (unsigned int)e.key.keysym.sym;
		}
	}
	unsigned int type;
	unsigned int symbol;
};*/

class Events: public GGE_module
{
	public:
		// gge_begin export ctor
		Events(shared_ptr<gge::GUI> gui);
		// gge_end export ctor
		~Events() = default;
        void set_gui(shared_ptr<gge::GUI> gui) { _gui = gui; } // to allow later initialization of gui

		void poll_events();
		const queue<int>& get_events();
		int pop_event(); // returns most recent event

		// this is for external script
		//static SDL_KeyCode get_key_codes();

		vector<int> get_mouse_position();

	private:
		SDL_Event _event; 
		queue<int> _events; // so that the queue doesn't need to be recreated each time
		SDL_helper _sdl_helper;
        Logger::Log& _log;
        shared_ptr<gge::GUI> _gui;
};

