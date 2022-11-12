#pragma once
#include <vector>
#include "commands/command.hpp"
#include <memory>
class Moduler;
class GGE_module;
class Core;
#include "registered_gge_modules.hpp"
using namespace std;
/*
 * keeps order of which commands to run in what order
 */

class Runner
{
	public:
		Runner(Moduler& m, Core& c);
		void exec_commands(); 
		void add_command(rgm module, int command, Moduler&);
		bool check_dependencies(); // true if all dependencies are OK
		// returns nr of commands
		int list_commands();
	private:
		shared_ptr<GGE_module> get_module(rgm module);

		Core& _core;
		Moduler& _moduler;
		std::vector<std::shared_ptr<Command>> _commands;
};
