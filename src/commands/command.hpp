#pragma once
#include <memory>
class GGE_module;

// gge_begin import commands

enum command {CMD};

// gge_end import commands

class Command
{
	public:
// gge_begin export ctor
		Command(
				std::shared_ptr<GGE_module> m, 
				std::shared_ptr<GGE_module> arg,
				command cmd
				);
// gge_end export ctor

		bool setup(std::shared_ptr<GGE_module> arg);
		virtual ~Command() = default;
	

		// do nothing unless defined
		virtual void execute() = 0;
		// TODO special for Game_loop
		virtual void execute(double d) {};

		// gge_begin string_commands
		// gge_end string_commands
	protected:
		std::shared_ptr<GGE_module> _module; // caller
		std::shared_ptr<GGE_module> _arg; // might be used as argument by caller

		/*
		 * specific command to be executetd
		 * in case of command containting multiple functions to execute
		 */
		command _cmd;
};
