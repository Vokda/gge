#include "runner.hpp"
#include "gge_module.hpp"
#include <iostream>
// gge_begin import headers
#include "commands/command.hpp"
#include "commands/game_loop_command.hpp"
#include "commands/events_command.hpp"
#include "commands/graphics_command.hpp"
#include "graphics.hpp"
// gge_end import headers
#include <regex>
#include <stdexcept>
#include <algorithm>
#include "moduler.hpp"
#include "core.hpp"
using namespace std;

Runner::Runner(Moduler& m, Core& c):
	_moduler(m), _core(c)
{}

void Runner::exec_commands()
{
	for(auto cmd: _commands)
	{
		cmd->execute();
	}
}

void Runner::add_command(rgm module, int command, rgm arg)
{
	shared_ptr<GGE_module> m = get_module(module);
	shared_ptr<GGE_module> parameter = get_module(arg);
	
	switch(module)
	{
		case EVENTS:
			_commands.push_back(
					make_shared<Events_command>(
						static_pointer_cast<Events>(m) // change to be the same as the other command classes
						)
					);
			break;
		case GAME_LOOP:
			_commands.push_back(make_shared<Game_loop_command>(
						static_pointer_cast<Game_loop>(m),  // change to be the same as the other command classes
						_core.get_delta_ref()
						)
					);
			break;
		case GRAPHICS:
			_commands.push_back(
					make_shared<Graphics_command>(
						m,
						command,
						parameter)
					);
			break;
//#include "runner_add_command_switch.generated"
		default:
			{
				invalid_argument ia(throw_message(__FILE__, "Cannot create command for", module));
				throw ia;
			}
			break;
	}

}

shared_ptr<GGE_module> Runner::get_module(rgm module)
{
	shared_ptr<GGE_module> m = _moduler[module];
	if(m == nullptr)
	{
		runtime_error e(throw_message(__FILE__, "module not initialized", module));
		throw e;
	}
	return m;
}

int Runner::list_commands()
{
	cout << "Commands (GGE module member functions) executed in the following order:"<<endl;
	int i = 0;
	for(auto cmd: _commands)
	{
		cout << i++ << ": " << cmd->get_command_string() << endl;
	}
	if(_commands.size() == 0)
	{
		cerr << __FILE__ << ": No commands issued! Quitting early!" << endl;
	}
	cout << endl;
	return _commands.size();
}

bool Runner::check_dependencies()
{
	return true;
}
