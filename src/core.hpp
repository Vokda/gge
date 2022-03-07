#ifndef CORE_HPP
#define CORE_HPP

#include <functional>
#include "sdl_helper.hpp"
#include <string>
class GGE_module;
class function;
class Chai_object;
class Initializer;
#include "moduler.hpp"

#include <chaiscript/chaiscript.hpp>
using namespace chaiscript; 

class Core
{
	public:

		Core();

		void init_game_object(Chai_object& co);

		// initializer for every other module
		template<typename T, typename ...Args>
			void init_module(Args... args) { _moduler.set_module(args...); }

		// for loading graphics (and sound and stuff too)
		void load_graphics(const string& path);

		// related to game loop
		void quit();

		void check_modules_initiated();

		void run();

		template<typename T>
			shared_ptr<T> get_module() { return _moduler.get_module<T>(); }

		//Moduler& get_moduler() { return _moduler; };

//#include "get_gge_modules.generated"

	private:

		bool _quit = false;

		double _delta = 1.0/60.0; // just some hard coded value to start things out

		Moduler _moduler;

		// some quick access pointers
		shared_ptr<Graphics> _graphics = nullptr;
		shared_ptr<Events> _events = nullptr;
		shared_ptr<Hex_grid> _grid = nullptr;
		shared_ptr<Texter> _texter = nullptr;
		shared_ptr<Scroller> _scroller = nullptr;

		// necessary for chaiscript member function functions to be called
		chaiscript::Boxed_Value _boxed_value;
		// function pointer to main game loop function defined in chaiscript
		std::unique_ptr<std::function<bool(Boxed_Value&, float)>> _game_loop;
		SDL_helper _sdl_helper;
};

#endif
