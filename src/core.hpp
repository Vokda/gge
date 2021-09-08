#ifndef CORE_HPP
#define CORE_HPP

#include <memory>
#include <functional>
#include "sdl_helper.hpp"
#include <string>
#include <vector>
class Graphics;
class Events;
class Hex_grid;
using namespace std;
class function;
class Chai_object;
class Texter;

#include <chaiscript/chaiscript.hpp>
using namespace chaiscript; 

class Core
{
	public:

		Core();

		// for initialzing modules
		enum Module {GRAPHICS, AUDIO, EVENT_HANDLER, GRID, GAME_LOOP, NR_MODULES};

		// MODULE INITIALIZERS
		void init_graphics(const std::string&&, size_t w, size_t h);
		void init_events();
		void init_grid(size_t w, size_t h, int size);
		void init_game_object(Chai_object&& co);

		// get modules (mainly for api)
		shared_ptr<Texter> get_texter();

		// for loading graphics (and sound and stuff too)
		void load_graphics(const string& path);

		void handle_events();

		// related to game loop
		void quit();

		void check_modules_initiated();

		void run();

	private:

		bool _quit = false;

		double _delta = 1.0/60.0; // just some hard coded value to start things out


		std::shared_ptr<Graphics> _graphics;
		std::shared_ptr<Events> _events;
		std::shared_ptr<Hex_grid> _grid;
		shared_ptr<Texter> _texter;

		// necessary for chaiscript member function functions to be called
		chaiscript::Boxed_Value _boxed_value;
		// function pointer to main game loop function defined in chaiscript
		std::unique_ptr<std::function<bool(Boxed_Value&, float)>> _game_loop;
		// function ptr to chai script 
		std::shared_ptr<std::function<void(Boxed_Value&, vector<int>)>> _event_handle;
		SDL_helper _sdl_helper;
};

#endif
