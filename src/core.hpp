#ifndef CORE_HPP
#define CORE_HPP

#include "sdl_helper.hpp"
#include <string>
class GGE_module;
#include "moduler.hpp"
#include "runner.hpp"
class Filer;

class Core
{
	public:

		Core(Filer& f);

		Filer& get_filer() { return _filer; }

		// quit the game
		void quit();

		void check_modules_initiated();
		void check_commands_order();

		// run game
		void run();

		shared_ptr<GGE_module> get_module(rgm m) { return _moduler[m]; }
		Moduler& get_moduler() { return _moduler; };

		void add_module(rgm module, shared_ptr<GGE_module> ptr);
		void add_command(rgm module, int command, rgm arg);

		double get_delta() { return _delta; };
		double& get_delta_ref() { return _delta; };

	private:
		bool _quit = false;
		double _delta = 1.0/60.0; // just some hard coded value to start things out
		double MAX_DELTA = 1.0/60.0; // TODO max 60 fps
		Moduler _moduler;
		Runner _runner;
		Filer& _filer;
		SDL_helper _sdl_helper;
};

#endif
