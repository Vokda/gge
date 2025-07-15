#pragma once
#include <string>
#include "../logger.hpp"
using namespace std;

class GGE_API;
class Script_engine
{
	public:
		Script_engine(GGE_API& gge_api): 
            _gge_api(gge_api), _log(Logger::make_category("script_engine")) {};
		virtual ~Script_engine() = default;

		void virtual read_file(const string& s) = 0;
		bool is_running() { return _is_running; }

		// return true if should continue to loop
		// the game loop it self should only be one frame of game logic
		virtual bool run_game_loop_once(double d) = 0;

        // call script function
        virtual void call_script_fn(void* fn) = 0;

	protected:
		// each script engine shoud add the standard gge api functions
		void virtual add_gge_api_functions() = 0;

		GGE_API& _gge_api;
		bool _is_running = false; 
        Logger::Log& _log;
};
