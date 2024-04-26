#include "core.hpp"
#include <sstream>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <algorithm>
#include "gge_modules/gge_module.hpp"
#include "filer.hpp"
#include "logger.hpp"
class Initializer;
using namespace std;

Core::Core(Filer& f):
	_runner(_moduler, *this),
	_filer(f),
    _logger(Logger::get_instance()),
	_log( _logger.add_category("Core")),
    _log_stream(_logger.get_category_stream("Core", log4cpp::Priority::INFO))
{
}

// MODULE INITIALIZERS END

void Core::run()
{
	_log.debug("running first loop"); 
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
	vector<registered_gge_module> important = {GRAPHICS, EVENTS, GRIDER, GAME_LOOP};
	for(auto m: important)
	{
		if(_moduler[m] == nullptr)
		{
			stringstream ss;
            ss << GGE_module::get_module_name(m) <<  " not initialized!"; 
            _logger.log("Core", log4cpp::Priority::WARN, ss.str());
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
	if(_runner.check_dependencies())
	{
        //_logger.log("Core", log4cpp::Priority::INFO, "Command order - OK");
        _log_stream <<"Command order - OK"; 
		int nr = _runner.list_commands();
		if(nr == 0)
        {
            _log.notice("Core", "No commands; exiting.");
			_quit = true;
        }
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

void Core::add_command(rgm module, int command, rgm arg)
{
	return _runner.add_command(module, command, arg);
}

