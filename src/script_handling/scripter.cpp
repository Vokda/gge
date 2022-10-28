#include <exception>
#include <iostream>
#include <functional>
#include <SDL2/SDL.h>
// use C solution until switching to C++17
// Running C++17 now, but why change a working concept
#include <sys/stat.h>

#include "scripter.hpp"
#include "gge_api.hpp"
#include "guile.hpp"
class GGE_API;
using namespace std;

Scripter::Scripter(const string& game_dir, GGE_API& ga):
	_gge_api(ga), _script_engine(make_unique<Guile>(ga))
{
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

	/*add_defaults(game_dir);
	_chai.add(_module_ptr);

	// include chai files; first the init file
	const string init_file = game_dir + "/" + "init.chai";
	// to get a member function from chai to work
	auto return_value = _chai.eval_file(init_file);
	const string game_obj_name = chaiscript::boxed_cast<string>(return_value);
	
	// get game loop and/or event handle function
	// assume both at the moment
	Chai_object co(_chai, game_obj_name);
	co.add_function("game_loop");
	co.add_function("event_handle");
	_gge_api.init_game_object(co);*/
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
