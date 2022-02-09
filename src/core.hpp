#ifndef CORE_HPP
#define CORE_HPP

#include <memory>
#include <functional>
#include "sdl_helper.hpp"
#include <string>
#include <vector>
#include "events.hpp"
class Graphics;
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

		// related to game loop
		void quit();

		void check_modules_initiated();

		void run();

		shared_ptr<Hex_grid> get_grid() { return _grid; }

		template<typename T>
			std::shared_ptr<T> get_module();

		template<>
			std::shared_ptr<Events> get_module() {return _events;}

	private:

		bool _quit = false;

		double _delta = 1.0/60.0; // just some hard coded value to start things out


		std::shared_ptr<Graphics> _graphics = nullptr;
		std::shared_ptr<Events> _events = nullptr;
		std::shared_ptr<Hex_grid> _grid = nullptr;
		shared_ptr<Texter> _texter = nullptr;

		// necessary for chaiscript member function functions to be called
		chaiscript::Boxed_Value _boxed_value;
		// function pointer to main game loop function defined in chaiscript
		std::unique_ptr<std::function<bool(Boxed_Value&, float)>> _game_loop;
		SDL_helper _sdl_helper;
};

#endif
