#ifndef CORE_HPP
#define CORE_HPP

#include <memory>
#include <functional>
#include "sdl_helper.hpp"
#include <string>
class Graphics;
class Events;
class Hex_grid;
using namespace std;
class function;

class Core
{
	public:

		Core() = default;

		// for initialzing modules
		enum Module {GRAPHICS, AUDIO, EVENT_HANDLER, GRID, GAME_LOOP, NR_MODULES};

		// MODULE INITIALIZERS
		void init_graphics(const std::string&&, size_t w, size_t h);
		void init_events();
		void init_grid(size_t w, size_t h, int size);
		void init_game_loop(const std::function<bool(float)>& f);

		// for loading graphics (and sound and stuff too)
		void load_graphics(const string& path);

		// fix soon
		bool handle_events();

		void check_modules_initiated();

		void run();

	private:

		bool _quit = false;
		double _delta = 1.0/60.0; // just some hard coded value to start things out


		std::shared_ptr<Graphics> _graphics;
		std::shared_ptr<Events> _events;
		std::shared_ptr<Hex_grid> _grid;
		// function pointer to main game loop function defined in chaiscript
		std::shared_ptr<std::function<bool(float)>> _game_loop;
		SDL_helper _sdl_helper;
};

#endif
