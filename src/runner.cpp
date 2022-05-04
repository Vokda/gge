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
	if(std::regex_match(s, mr, e))
	{
		cout << "number of matches" << endl;
		cout << mr.size() << endl;
		string class_name = mr.str(1);
		string function_name = mr.str(2);
		string argument = mr.size() > 2 ? mr.str(3) : "";

		shared_ptr<GGE_module> m = nullptr;
		rgm module_type = NONE;
		shared_ptr<GGE_module> arg = nullptr;
		rgm arg_type = NONE;

		// class
		if(class_name == "graphics")
		{
			module_type = GRAPHICS;
			m = moduler[module_type];
		}
		// member function
		if(function_name == "clear_screen")
		{
			arg_type = NONE;
			arg = nullptr;
		}

		switch(module_type)
		{
			case GRAPHICS:
				_commands.push_back(
						make_shared<Graphics_command>(m, module_type, arg, arg_type,GRAPHICS_CLEAR_SCREEN)
						);
				break;
			default:
				throw "module_type " + to_string(module_type) + " not recognized!";
		}
	}
	else
	{
		throw "command '" + cmd_str + "' not recognized!";
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

/*int string_to_command(const string& cmd_str)
{
	return 
}*/
