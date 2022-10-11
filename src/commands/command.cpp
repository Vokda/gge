#include "command.hpp"

using namespace std;

Command::Command(
				std::shared_ptr<GGE_module> m, 
				std::shared_ptr<GGE_module> arg,
				command cmd)
{
	_module = m;
	_arg = arg;
	_cmd = cmd;
}

bool Command::setup(std::shared_ptr<GGE_module> arg) 
{
	_arg = arg; 
	return true;
}
