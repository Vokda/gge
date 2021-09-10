#include <exception>
#include <iostream>
#include <functional>
// use C solution until switching to C++17
// Running C++17 now, but why change a working concept
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
	_gge_api(ga),
	_module_ptr(chaiscript::ModulePtr(new chaiscript::Module()))
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

	add_defaults(game_dir);
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
	_initializer.game_object(co);
}

void Scripter::add_defaults(const string& game_dir)
{
	// add global classes from GGE
	add_class<Initializer, Core&>(
			"Initializer",
			{ chaiscript::constructor<Initializer(Core&)>() },
			{
				{chaiscript::fun(&Initializer::graphics), "graphics"},
				{chaiscript::fun(&Initializer::events), "events"},
				{chaiscript::fun(&Initializer::grid), "grid"},
			},
			&_initializer,
			"gge_initializer",
			true
			);

	add_class<GGE_API, Core&>(
			"GGE_API",
			{ chaiscript::constructor<GGE_API(Core&)>() },
			{ 
				{chaiscript::fun<const string (GGE_API::*)(void)>(&GGE_API::hello), "hello"},
				{chaiscript::fun<size_t (GGE_API::*)(const std::string&, int, int)>(&GGE_API::create_text), "create_text"},
				{chaiscript::fun
					<size_t // return value
						(GGE_API::*)(const std::string&, std::vector<int>, std::vector<int>, int)> // args
					(&GGE_API::create_text), "create_text"}, // fn pointer and fn name
				{chaiscript::fun<std::vector<int> (GGE_API::*)(void)>(&GGE_API::get_mouse_position), "get_mouse_position"}
			},
			&_gge_api,
			"gge_api",
			true
			);

	// add global vars
	_chai.add_global(chaiscript::var(game_dir), "game_dir");
	typedef std::vector<int> stl_vector_int;
	chaiscript::bootstrap::standard_library::vector_type<stl_vector_int>("stl_vector_int", *_module_ptr);
	

	_chai.add(chaiscript::vector_conversion<stl_vector_int>());



}
