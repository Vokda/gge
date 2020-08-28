#include <exception>
#include <iostream>
#include <functional>
// use C solution until switching to C++17
#include <sys/stat.h>

// chaiscript
#include <chaiscript/utility/utility.hpp>

#include "scripter.hpp"
#include "initializer.hpp"
#include "chai_object.hpp"
#include "core.hpp"
class GGE_API;
using namespace std;

Scripter::Scripter(const string& game_dir, Initializer& i, GGE_API& ga):
	_initializer(i),
	_gge_api(ga)
{
	// check if dir
	struct stat file_stat;
	stat(game_dir.c_str(), &file_stat);
	if(file_stat.st_mode == S_IFDIR)
	{
		string s = "Scripter: " + game_dir + " not a directory!";
		throw s.c_str();
	}

	add_defaults(game_dir);

	cout << "Game directory: " << game_dir << endl;
	const string init_file = game_dir + "/" + "init.chai";
	// to get a member function from chai to work
	auto return_value = _chai.eval_file(init_file);
	const string game_obj_name = chaiscript::boxed_cast<string>(return_value);
	
	// get game loop and/or event handle function
	// assume both at the moment
	Chai_object co(_chai, game_obj_name);
	co.add_function("game_loop");
	co.add_function("event_handle");
	_initializer.game_object(co);
}

void Scripter::add_defaults(const string& game_dir)
{
	add_class<Initializer, Core&>(
			"Initializer",
			{ chaiscript::constructor<Initializer(Core&)>() },
			{
				{chaiscript::fun(&Initializer::graphics), "graphics"},
				{chaiscript::fun(&Initializer::events), "events"},
				{chaiscript::fun(&Initializer::grid), "grid"},
			},
			&_initializer,
			"gge_initializer"
			);

	add_class<GGE_API, Core&>(
			"GGE_API",
			{ chaiscript::constructor<GGE_API(Core&)>() },
			{ 
				//{ fun(&GGE_API::get_sdl_keycodes), "get_sdl_keycodes" }
			},
			&_gge_api,
			"gge_api"
			);


	_chai.add(chaiscript::var(game_dir), "game_dir");

	_chai.add(chaiscript::bootstrap::standard_library::vector_type<std::vector<int>>("Vector_int"));
	_chai.add(chaiscript::vector_conversion<std::vector<int>>());
}
