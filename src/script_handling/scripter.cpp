#include <exception>
#include <iostream>
#include <functional>
#include <SDL2/SDL.h>
// use C solution until switching to C++17
// Running C++17 now, but why change a working concept
#include <sys/stat.h>

#include "scripter.hpp"
#include "script_engine.hpp"
#include "guile.hpp"
#include "script_engine.hpp"
#include "gge_api.hpp"
//#include "../core.hpp"
//class GGE_API;
using namespace std;

Scripter::Scripter(const string& game_dir, GGE_API& ga):
	_script_engine(make_shared<Guile>(ga))
{
	ga.set_script_engine(_script_engine);

	// check if dir
	struct stat file_stat;
	stat(game_dir.c_str(), &file_stat);
	if(file_stat.st_mode == S_IFDIR)
	{
		string s = "Scripter: " + game_dir + " not a directory!";
		throw s.c_str();
	}

	cout << "Game directory: " << game_dir << endl;

	// TODO if script engine type look for associate file type
	string file_name = game_dir + "/init.scm";
	_script_engine->read_file(file_name);

}

bool Scripter::is_script_engine_running()
{ 
	return _script_engine->is_running(); 
}

/*
void Scripter::add_defaults(const string& game_dir)
{
	// add global classes from GGE
	typedef std::vector<int> stl_vector_int;
	add_class<GGE_API, Core&>(
			"GGE_API",
			{ chaiscript::constructor<GGE_API(Core&)>() }, // constructor
			{ 
				{chaiscript::fun<const string (GGE_API::*)(void)>(&GGE_API::hello), "hello"},
#include "gge_api_defaults.generated"
			},
			&_gge_api,
			"gge_api",
			true
			);

	// add global vars
	_chai.add_global(chaiscript::var(game_dir), "game_dir");
	chaiscript::bootstrap::standard_library::vector_type<stl_vector_int>("stl_vector_int", *_module_ptr);
	_chai.add(chaiscript::vector_conversion<stl_vector_int>());
}
*/
