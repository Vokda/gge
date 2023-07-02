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
class Filer;
class Configuration;

class Scripter
{
	public:
		Scripter(Filer& filer, GGE_API&, const Configuration& config);
		bool is_script_engine_running();

		enum scripting_language {NOT_SUPPORTED, GUILE};

	private:

		shared_ptr<Script_engine> _script_engine; 
		Filer& _filer;
};

#endif
