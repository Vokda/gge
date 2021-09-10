#pragma once

#include <vector>
#include <SDL2/SDL.h>
class SDL_helper;
using namespace std;

class Events
{
	public:
		Events(SDL_helper&);

		const vector<int>& get_events();
		// this is for the chaiscript 
		static SDL_KeyCode get_key_codes();

		vector<int> get_mouse_position();

	private:
		SDL_Event _event; 
		vector<int> _events; // so that the vector doesn't need to be recreated each time
		SDL_helper& _sdl_helper;
};
