#pragma once
#include <string>
using namespace std;

class GGE_API;
class Script_engine
{
	public:
		Script_engine(GGE_API& gge_api): _gge_api(gge_api) {};
		virtual ~Script_engine() = default;

		void virtual read_file(const string& s) = 0;
		bool is_running() { return _is_running; }
	protected:
		// each script engine shoud add the standard gge api functions
		void virtual add_gge_api_functions() = 0;

		GGE_API& _gge_api;
		bool _is_running; 
};
