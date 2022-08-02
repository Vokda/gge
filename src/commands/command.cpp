#include "command.hpp"

using namespace std;

Command::Command(
				std::shared_ptr<GGE_module> m, 
				rgm type,
				std::shared_ptr<GGE_module> arg,
				rgm arg_type,
				command cmd)
{
	_module = m;
	_type_m = type;
	_arg = arg;
	_type_a = arg_type;
}

bool Command::setup(std::shared_ptr<GGE_module> arg) 
{
	_arg = arg; 
	return true;
}
