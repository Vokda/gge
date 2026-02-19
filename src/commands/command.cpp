#include "command.hpp"
#include "../gge_modules/gge_module.hpp"

Command::Command(shared_ptr<GGE_module> m,  shared_ptr<GGE_module> arg, int command):
	_log(Logger::get_instance().add_category(m->get_type_string() + " command " + to_string(command)))
{
	_module = m;
	_arg = arg;
	_cmd = command;
}

int Command::get_command()
{
	return _cmd;
}

shared_ptr<GGE_module> Command::get_argument()
{
	return _arg;
}

shared_ptr<GGE_module> Command::get_module()
{
	return _module;
}

bool Command::is_valid_command() const
{
	return _cmd < 0; // true if -1 (default value) unless command child class specifies otherwise.
}
