/*
 * Defines the communications between engine and script
 */
#ifndef SCRIPTER_HPP
#define SCRIPTER_HPP

#include "gge_api.hpp"
#include <functional>
#include "guile.hpp"
using namespace std;

class Scripter
{
	public:
		Scripter(const string& game_directory, GGE_API& ga);
		bool is_script_engine_runnig() { return _is_running; }

	private:
		GGE_API& _gge_api;
		bool _is_running;
		// change to a more generic version some day
		Guile _script;
};

#endif
