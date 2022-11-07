#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "gge_module.hpp"
#include "sdl_helper.hpp"
using namespace std;

enum device {KEYBOARD, MOUSE};

struct event
{
	event()
	{
		type = 0;
		symbol = 0;
	}
	event(SDL_Event& e)
	{
		type = e.type;
		if(SDL_MOUSEBUTTONDOWN or SDL_MOUSEBUTTONUP)
		{
			symbol = (unsigned int) e.button.button;
		}
		else if(SDL_KEYDOWN or SDL_KEYUP)
		{
			symbol = (unsigned int)e.key.keysym.sym;
		}
	}
	unsigned int type;
	unsigned int symbol;
};

class Events: public GGE_module
{
	public:
		// gge_begin export ctor
		Events();
		// gge_end export ctor
		~Events() = default;

		const vector<int>& get_events();
		// this is for the chaiscript 
		static SDL_KeyCode get_key_codes();

		vector<int> get_mouse_position();

	private:
		SDL_Event _event; 
		vector<int> _events; // so that the vector doesn't need to be recreated each time
		SDL_helper _sdl_helper;
};

