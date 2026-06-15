/*
 * Defines the communications between engine and script
 */
#ifndef SCRIPTER_HPP
#define SCRIPTER_HPP

#include <string>
#include <memory>
using namespace std;

class Script_engine;
class GGE_API;
struct Configuration;
#include "../logger.hpp"

class Scripter
{
	public:
		Scripter(const string& main_file, GGE_API&, const string& scripting_language);
		bool is_script_engine_running();

		enum scripting_language {NOT_SUPPORTED, GUILE};

	private:
		scripting_language parse_language_string(const string& s);

		shared_ptr<Script_engine> _script_engine; 
        Logger::Log& _log;
};

#endif
