#pragma once
#include <string>
#include <memory>
using namespace std;
#include "../gge_module.hpp"

class Command
{
	public:
		// if multiple commands set command to >= 0
		Command(int command = -1, shared_ptr<GGE_module> arg = nullptr);
		virtual ~Command() = default;

		virtual const string get_command_string() const = 0;
		virtual void execute() = 0;
	protected:

		/*
		 * specific command to be executed
		 * in case of command containting multiple functions to execute
		 */
		int _cmd;
		shared_ptr<GGE_module> _arg;
};
