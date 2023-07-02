#include "configurer.hpp"
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include "filer.hpp"
using namespace std;

Configurer::Configurer(const Filer& f, GGE_API& ga):
	_gge_api(ga)
{
	string cfg = f.in_game_dir("gge.cfg");
	read_config(cfg);
}

const Configuration& Configurer::read_config(const string& config_name)
{
	ifstream config(config_name, std::ifstream::in);

	if(!config.is_open())
	{
		cout << "Configurer: failed to open " << config_name << endl;
	}
	else
	{
		cout << "Reading config" << config_name << endl;
		string command;
		vector<string> args;
		string s;
		while(std::getline(config, s))
		{
			stringstream line(s);
			line >> command;

			if(command.find_first_of("#") != std::string::npos) continue;

			to_lower(command);
			string a;
			cout << command << endl;
			while(line >> a)
			{
				to_lower(a);
				args.push_back(a);
				cout << '\t' << a << endl;
			}

			store_config(command, args);
		}
	}

	return _config;
}

void Configurer::to_lower(string& s)
{
	std::transform(s.begin(), s.end(), s.begin(),
			[](unsigned char c){ return std::tolower(c); });
}

void Configurer::store_config(const string& command, const vector<string>& args)
{
	if(command == "script")
	{
		if(args.front() == "guile")
			_config.script = Scripter::GUILE;
		else
			_config.script = Scripter::NOT_SUPPORTED;
	}
	else if(command == "game_file")
	{
		_config.game_file_name = args.front();
	}
	else if(command == "game_loop_function")
	{
		_config.game_loop_name = args.front();
	}
	else
	{
		stringstream ss;
		ss << "configuration not recognized: " << command << " ";
		for(string s : args)
		{
			ss << s << " ";
		}
		ss << endl;
		throw runtime_error(ss.str());
	}
}


const Configuration& Configurer::get_configuration() const
{
	return _config;
}
