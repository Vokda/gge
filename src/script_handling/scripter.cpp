#include <exception>
#include <iostream>
#include <functional>
#include <SDL2/SDL.h>

#include "scripter.hpp"
#include "script_engine.hpp"
#include "guile.hpp"
#include "script_engine.hpp"
#include "gge_api.hpp"
#include "../filer.hpp"
//class GGE_API;
using namespace std;

Scripter::Scripter(Filer& f, GGE_API& ga):
	_script_engine(make_shared<Guile>(ga)), // TODO guile is hard coded atm
	_filer(f)
{
	ga.set_script_engine(_script_engine);

	cout << "Game directory: " << _filer.get_game_root_dir() << endl;

	// TODO if script engine type look for associate file type
	string file_name = _filer.in_game_dir("init.scm");
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
