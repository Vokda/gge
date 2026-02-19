#include "ticker_command.hpp"
#include <concepts>
#include <sstream>
#include <stdexcept>
#include "../gge_modules/texter.hpp"
#include "../gge_modules/agenter.hpp"
#include "../gge_modules/spriter.hpp"

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
	// get the module and call tick on it
	switch(_tickable_module->get_type())
	{
		case(rgm::TEXTER):
			{
				auto texter = static_pointer_cast<Texter>(_tickable_module);
				texter->tick();
				break;
			}
		case(rgm::AGENTER):
			{
				auto agenter = static_pointer_cast<Agenter>(_tickable_module);
				agenter->tick();
				break;
			}
		case(rgm::SPRITER):
			{
				auto spriter = static_pointer_cast<Spriter>(_tickable_module);
				spriter->tick();
				break;
			}
		default:
			throw domain_error("Ticker command not recognized " + to_string(_tickable_module->get_type()));
			break;
	}
}

const string Ticker_command::get_command_string() const
{
	stringstream ss;
	switch(_tickable_module->get_type())
	{
		case(rgm::TEXTER):
			ss << "Texter";
			break;
		case (rgm::AGENTER):
			ss << "Agenter";
			break;
		case (rgm::SPRITER):
			ss << "Spriter";
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
