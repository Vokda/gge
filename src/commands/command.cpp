#include "command.hpp"

Command::Command(int command, shared_ptr<GGE_module> arg)
{
	_cmd = command;
	_arg = arg;
}
