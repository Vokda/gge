/*
 * Defines the communications between engine and script
 */
#ifndef SCRIPTER_HPP
#define SCRIPTER_HPP

#include "gge_api.hpp"
#include <functional>
#include "script_engine.hpp"
#include <memory>
using namespace std;

class Scripter
{
	public:
		Scripter(const string& game_directory, GGE_API& gge_api);
		bool is_script_engine_runnig() { return _script_engine->is_running(); }

	private:
		GGE_API& _gge_api;
		unique_ptr<Script_engine> _script_engine;
};

#endif
