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
#include "runner.hpp"

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

		void add_command(const string&);
		//bool add_command(const string& cmd);

	private:

		bool _quit = false;

		double _delta = 1.0/60.0; // just some hard coded value to start things out

		Moduler _moduler;

		Runner _runner;

		// necessary for chaiscript member function functions to be called
		chaiscript::Boxed_Value _boxed_value;
		// function pointer to main game loop function defined in chaiscript
		std::unique_ptr<std::function<bool(Boxed_Value&, float)>> _game_loop = nullptr;
		SDL_helper _sdl_helper;
};

#endif
