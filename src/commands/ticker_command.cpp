#include "ticker_command.hpp"
#include <concepts>
#include <sstream>
#include <stdexcept>
#include "../texter.hpp"

Ticker_command::Ticker_command(
				shared_ptr<GGE_module> tickable_module, 
				shared_ptr<GGE_module> arg,
				int command):
	Command(tickable_module, arg, command)
{
	_tickable_module = tickable_module;
}

void Ticker_command::execute()
{
	switch(_cmd)
	{
		case(TEXTER):
			{
				auto texter = static_pointer_cast<Texter>(_tickable_module);
				texter->tick();
				break;
			}
		default:
			throw domain_error("Ticker command not recoqnized " + to_string(_cmd));
			break;
	}
}

const string Ticker_command::get_command_string() const
{
	stringstream ss;
	switch(_cmd)
	{
		case(TEXTER):
			ss << "Texter";
			break;
		default:
			return "wonky ticker command!";
			break;
	}
	ss << "->tick()";
	return ss.str();
}

bool Ticker_command::is_valid_command() const
{
	return _cmd > -1 && _cmd < MAX;
}
