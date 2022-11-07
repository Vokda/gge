#pragma once
#include <vector>
#include "commands/command.hpp"
#include <memory>
class Moduler;
/*
 * keeps order of which commands to run in what order
 */

class Runner
{
	public:
		Runner();
		void exec_commands(); 
		void add_command(const std::string& cmd, Moduler&);
		bool check_dependencies(); // true if all dependencies are OK
		// returns nr of commands
		int list_commands();
	private:
		command string_to_command(const std::string& cmd_str);
		std::vector<std::shared_ptr<Command>> _commands;
};
