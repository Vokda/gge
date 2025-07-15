#include "runner.hpp"
#include "gge_modules/gge_module.hpp"
// gge_begin import headers
#include "commands/command.hpp"
#include "commands/game_loop_command.hpp"
#include "commands/events_command.hpp"
#include "commands/graphics_command.hpp"
#include "commands/ticker_command.hpp"
// gge_end import headers
#include <stdexcept>
#include <sstream>
#include "moduler.hpp"
#include "core.hpp"
using namespace std;

Runner::Runner(Moduler& m, Core& c):
	_core(c), _moduler(m), _log(Logger::make_category("Runner"))
{
    _log.info("OK");
}

void Runner::exec_commands()
{
	for(auto cmd: _commands)
	{
        // _log.debug("Running command %s", cmd->get_module()->get_type_string() );
		cmd->execute();
	}
}

void Runner::add_command(rgm module, int command, rgm arg)
{
	shared_ptr<GGE_module> gge_module = get_module(module);
	shared_ptr<GGE_module> parameter = get_module(arg);
    _log.debug("adding command: executor %s, command %i, arg %s",
            GGE_module::get_module_name(module).c_str(),
            command,
            GGE_module::get_module_name(arg).c_str()
            );
	
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
		case TEXTER:
			_commands.push_back(
					make_shared<Ticker_command>(
						gge_module,
						get_module(NONE),
						command
						));
			break;

//#include "runner_add_command_switch.generated"
		default:
			{
				invalid_argument ia(throw_message(__FILE__, "Cannot create command for", module));
				throw ia;
			}
			break;
	}
    _log.debug("finished adding command");
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
    _log.info("Commands (GGE module member functions) executed in the following order:");
	int i = 0;
	for(auto cmd: _commands)
	{
        _log.info("%i: %s", i++, cmd->get_command_string().c_str());
	}
	if(_commands.size() == 0)
	{
        _log.notice("No commands issued! Quitting early!");
	}
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
