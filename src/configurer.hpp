/*
 * Reads and parses configuration file (gge.cfg)
 */

#pragma once
class GGE_API;
class Filer;
#include <string>
#include <vector>
#include "script_handling/scripter.hpp"

struct Configuration
{
	Scripter::scripting_language script;
	string game_file_name;
	string game_loop_name; // within game
};

class Configurer
{
	public:
		Configurer(const Filer& f, GGE_API&);

		const Configuration& get_configuration() const;

	private:
		const Configuration& read_config(const std::string&);
		void store_config(const string& command, const vector<string>& args);
		void to_lower(string& s);

		GGE_API& _gge_api;
		Configuration _config;
};
