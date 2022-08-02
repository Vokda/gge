#include "runner.hpp"
#include "gge_module.hpp"
#include <iostream>
// gge_begin import headers
#include "commands/command.hpp"
#include "commands/graphics_command.hpp"
// gge_end import headers
#include <regex>
#include <algorithm>
#include "moduler.hpp"
#include <exception>

using namespace std;

Runner::Runner()
{}

void Runner::exec_commands()
{
	for(auto cmd: _commands)
	{
		cmd->execute();
	}
}

void Runner::add_command(const string& cmd_str, Moduler& moduler)
{
	std::string s = cmd_str;
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	regex e("(.+)\\.(.+)\\((.*)\\)");
	std::smatch mr;
	cout << "trying to add command '"<< s << "'" << endl;
	if(std::regex_match(s, mr, e))
	{
		cout << "number of matches" << endl;
		cout << mr.size() << endl;
		string class_name = mr.str(1);
		string function_name = mr.str(2);
		string argument = mr.size() > 2 ? mr.str(3) : "";

		cout << "matches:" << endl;
		cout << "class_name " << class_name << endl;
		cout << "function_name " << function_name << endl;
		cout << "argument " << argument << endl;

		shared_ptr<GGE_module> m = nullptr;
		rgm module_type = NONE;
		shared_ptr<GGE_module> arg = nullptr;
		rgm arg_type = NONE;

#include "runner_add_command_switch.generated"

	}
	else
	{
		std::string s = "command '" + cmd_str + "' not recognized!";
		throw invalid_argument(s);
	}
}

void Runner::list_commands()
{
	cout << "Commands (module functions) executed in the following order:"<<endl;
	int i = 0;
	for(auto cmd: _commands)
	{
		// TODO
		cout << i++ << ": " << "command" << endl;
	}
	cout << endl;
}

bool Runner::check_dependencies()
{
	return true;
}

/*int string_to_command(const string& cmd_str)
{
	return 
}*/
