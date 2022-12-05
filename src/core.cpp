#include "core.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <algorithm>
#include "gge_module.hpp"
class Initializer;
using namespace std;

Core::Core():
	_runner(_moduler, *this)
{
}

// MODULE INITIALIZERS END

void Core::run()
{
#ifdef DEBUG
	cout << "Core: running first loop" << endl;
#endif
	// main loop
	while(not _quit)
	{
		auto start = std::chrono::steady_clock::now();

		_runner.exec_commands();

		auto end = std::chrono::steady_clock::now();

		// calculate delta
		std::chrono::duration<double> elapsed_seconds = end - start;
		_delta = elapsed_seconds.count();
		
		// TODO max fps 
		double d = MAX_DELTA - _delta;
		if(d > 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(long(d*1000)));
		}
	}
}

void Core::check_modules_initiated()
{
	_moduler.list_modules();

	// probably important modules
	vector<registered_gge_module> important = {GRAPHICS, EVENTS, GRID, GAME_LOOP};
	for(auto m: important)
	{
		if(_moduler[m] == nullptr)
		{
			cerr << "Warning: " << GGE_module::get_module_name(m) <<  " not initialized!" << endl;
		}
	}

	if(not _moduler[GAME_LOOP])
	{
		std::domain_error de("No game loop provided!");
		throw de; 
	}
}

void Core::check_commands_order()
{
	cout << "Command order - ";
	if(_runner.check_dependencies())
	{
		cout << "OK" << endl;
		int nr = _runner.list_commands();
		if(nr == 0)
			_quit = true;
	}
	else
	{
		std::domain_error de("Command order not possible!");
		throw de;
	}
}

void Core::quit()
{
	_quit = true;
}

void Core::add_module(rgm m, shared_ptr<GGE_module> ptr)
{
	_moduler.set_module(m, ptr);
}

void Core::add_command(rgm module, int command)
{
	return _runner.add_command(module, command, _moduler);
}

