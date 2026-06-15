#include <exception>
#include <iostream>
#include <functional>
#include <SDL2/SDL.h>
#include <algorithm>

#include "../configurer.hpp"
#include "scripter.hpp"
#include "script_engine.hpp"
#include "guile.hpp"
#include "script_engine.hpp"
#include "gge_api.hpp"
//class GGE_API;
using namespace std;

Scripter::Scripter(const string& main_file, GGE_API& ga, const string& scripting_language):
	_log(Logger::make_category("Scripter"))
{
	switch(parse_language_string(scripting_language))
	{
		case GUILE:
			_script_engine = make_shared<Guile>(ga);
			break;
		default:
			throw runtime_error("Scripting language " + scripting_language + " is not supported!");
			break;
	}
	ga.set_script_engine(_script_engine);

    try
    {
        _log.info("Reading file: %s", main_file.c_str());
        _script_engine->read_file(main_file);
    }
    catch (std::exception& e)
    {
        _log.fatal("Guile error: %s", e.what());
        throw runtime_error("Unable to continue Guile execution!");
    }
}

bool Scripter::is_script_engine_running()
{ 
	return _script_engine->is_running(); 
}

Scripter::scripting_language Scripter::parse_language_string(const string& s)
{
	string lower_s = s;
	std::transform(lower_s.begin(), lower_s.end(), lower_s.begin(), ::tolower);
	if (lower_s == "guile")
		return GUILE;
	else
		return NOT_SUPPORTED;
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
