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
	shared_ptr<GGE_module> gge_module = get_module(module);
	shared_ptr<GGE_module> parameter = get_module(arg);
	
	switch(module)
	{
		case EVENTS:
			_commands.push_back(
					make_shared<Events_command>(
						static_pointer_cast<Events>(gge_module), // change to be the same as the other command classes
						get_module(NONE)
						)
					);
			break;
		case GAME_LOOP:
			_commands.push_back(make_shared<Game_loop_command>(
						static_pointer_cast<Game_loop>(gge_module),  // change to be the same as the other command classes
						get_module(NONE),
						_core.get_delta_ref()
						)
					);
			break;
		case GRAPHICS:
			_commands.push_back(
					make_shared<Graphics_command>(
						gge_module,
						parameter,
						command)
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
	bool error = false;
	stringstream ss;
	for(auto cmd: _commands)
	{

		int cmd_command = cmd->get_command();

		shared_ptr<GGE_module> gge_module_ptr = cmd->get_module();
		if(gge_module_ptr == nullptr or _moduler[gge_module_ptr->get_type()] == nullptr)
		{
			ss << __FILE__ << ": module not initiated for command " << cmd->get_command_string() << endl;
			error = true;
		}

		gge_module_ptr = cmd->get_argument();
		if(gge_module_ptr == nullptr or _moduler[gge_module_ptr->get_type()] == nullptr)		
		{
			ss << __FILE__ << ": module for argument not initiated for command " << cmd->get_command_string() << endl;
			error = true;
		}

		if(not cmd->is_valid_command())
		{
			ss << __FILE__ <<  ": command "+to_string(cmd_command)+" not valid for " << cmd->get_command_string() << endl;
			error = true;
		}
	}

	if(error)
	{
		logic_error le(ss.str());
		throw(le);
		return false;
	}
	return true;
}
