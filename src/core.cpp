#include "core.hpp"
#include <iostream>
#include <chrono>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include "registered_gge_modules.hpp"
class Initializer;
using namespace std;

Core::Core()
{
}

// MODULE INITIALIZERS END

void Core::run()
{
	// main loop
	while(not _quit)
	{
		auto start = std::chrono::steady_clock::now();

		_runner.exec_commands();

		// game logic
		// game can be quit from inside the game loop by returning true
		//_quit = (*_game_loop)(_boxed_value, _delta);

		auto end = std::chrono::steady_clock::now();

		// calculate delta
		std::chrono::duration<double> elapsed_seconds = end - start;
		_delta = elapsed_seconds.count();
	}
}

void Core::check_modules_initiated()
{
	_moduler.list_modules();

	// probably important modules
	vector<registered_gge_module> important = {GRAPHICS, EVENTS, GRID};
	for(auto m: important)
	{
		if(_moduler[m] == nullptr)
		{
			cerr << "Warning: " << GGE_module::get_module_name(m) <<  " not initiated!" << endl;
		}
	}

	if(not _game_loop)
	{
		std::domain_error de("No game loop provided!");
		throw de; 
	}

	_runner.list_commands();
}

void Core::quit()
{
	_quit = true;
}

void Core::add_command(const string & cmd)
{
	return _runner.add_command(cmd, _moduler);
}
