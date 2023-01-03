#pragma once
#include <string>
#include <memory>
using namespace std;
#include "../gge_module.hpp"

class Command
{
	public:
		// if multiple commands set command to >= 0
		Command(shared_ptr<GGE_module> module,  shared_ptr<GGE_module> arg, int command = -1);
		virtual ~Command() = default;

		virtual const string get_command_string() const = 0;
		virtual void execute() = 0;

		int get_command();
		shared_ptr<GGE_module> get_argument();
		shared_ptr<GGE_module> get_module();

		virtual bool is_valid_command() const;

	protected:

		/*
		 * specific command to be executed
		 * in case of command containting multiple functions to execute
		 */
		int _cmd;
		shared_ptr<GGE_module> _arg;
		shared_ptr<GGE_module> _module;

};
