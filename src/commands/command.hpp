#pragma once
#include <string>
using namespace std;

class Command
{
	public:
		// if multiple commands set command to >= 0
		Command(int command = -1);
		virtual ~Command() = default;

		virtual const string get_command_string() const = 0;
		virtual void execute() = 0;

		// gge_begin string_commands
		// gge_end string_commands
	protected:

		/*
		 * specific command to be executed
		 * in case of command containting multiple functions to execute
		 */
		int _cmd;
};
