#pragma once
#include "command.hpp"
#include "../gge_module.hpp"

class Ticker_command: public Command
{
	public:
		Ticker_command(
				shared_ptr<GGE_module> tickable_module, 
				shared_ptr<GGE_module> arg,
				int command);
		void execute();
		enum command {TEXTER, MAX};
		const string get_command_string() const;
		bool is_valid_command() const;
	private:
		shared_ptr<GGE_module> _tickable_module;
};
