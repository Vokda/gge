#ifndef CORE_HPP
#define CORE_HPP

#include <functional>
#include "sdl_helper.hpp"
#include <string>
#include "gge_module_initializer.hpp"
class GGE_module;
class function;
#include "moduler.hpp"
#include "runner.hpp"

class Core
{
	public:

		Core();

		// initializer for every other module
		template<typename ...Args>
			void init_module(rgm m, Args... args) 
			{ 
				cout << "core hej" << endl;
				auto ptr = _gge_initializer.initialize(m, args...);
				_moduler.set_module(m, ptr); 
			}

		// for loading graphics (and sound and stuff too)
		void load_graphics(const string& path);

		// related to game loop
		void quit();

		void check_modules_initiated();

		void run();

		shared_ptr<GGE_module> get_module(rgm m) { return _moduler[m]; }

		Moduler& get_moduler() { return _moduler; };

		void add_command(const string&);
		//bool add_command(const string& cmd);

	private:

		bool _quit = false;

		double _delta = 1.0/60.0; // just some hard coded value to start things out

		Moduler _moduler;

		Runner _runner;

		// necessary for chaiscript member function functions to be called
		/*chaiscript::Boxed_Value _boxed_value;
		// function pointer to main game loop function defined in chaiscript
		std::unique_ptr<std::function<bool(Boxed_Value&, float)>> _game_loop = nullptr;*/
		bool _game_loop; //TODO
		SDL_helper _sdl_helper;
		GGE_module_initializer _gge_initializer;
};

#endif
