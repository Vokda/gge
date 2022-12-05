#include "guile.hpp"
#include <stdexcept>
#include <string>
#include "gge_api.hpp"
#include <cstdarg>
//#include "../registered_gge_modules.hpp"
#include "guile/gge_api_wrapper.hpp"

static Guile* guile;

Guile::Guile(GGE_API& ga):
	Script_engine(ga)
{
	guile = this;
	// handle through config
	//putenv("GUILE_LOAD_PATH=");
	scm_init_guile(); //not cross platform compatible
	char arg1[] = "--debug";
	char *argv = arg1;
	//scm_boot_guile(1, &argv, guile_main, 0); 
	//scm_with_guile(&guile_main, NULL);
	scm_set_program_arguments(1, &argv, NULL);
	add_gge_api_functions();
}

void Guile::read_file(const string& s)
{
	_scm = scm_c_primitive_load(s.c_str());
	// game class should be included by now
	SCM game_module = scm_c_resolve_module("game");
	SCM game_loop_fn = scm_c_module_lookup(game_module, "game_loop");
	_scm_game_loop = scm_variable_ref(game_loop_fn);
	//_scm_game_loop = scm_variable_ref(scm_c_lookup("game:game_loop"));
	if(_scm_game_loop == NULL)
	{
		runtime_error re("No game loop procedure set in Guile called 'game_loop'");
		throw re;
	}
}

bool Guile::run_game_loop_once(double delta)
{
	//scm_call_1(_scm_game_loop, scm_from_double(delta));
	SCM scm = scm_call_1(_scm_game_loop, scm_from_double(delta));
	bool quit = scm_to_bool(scm);
	return quit;
}

void Guile::add_gge_api_functions()
{
	init_gge_api_wrapper(&_gge_api);

	SCM current_module = scm_c_define_module("gge", NULL, NULL);
	SCM prev_module = scm_set_current_module(current_module);

	// gge_begin read subs
	scm_c_define_gsubr("hello", 0, 0, 0, (scm_t_subr) gge_api_hello);

	scm_c_define_gsubr("init_graphics", 3, 0, 0, (scm_t_subr) init_graphics);
	scm_c_define_gsubr("init_events", 0, 0, 0, (scm_t_subr) init_events);
	scm_c_define_gsubr("init_grid", 3, 0, 0, (scm_t_subr) init_grid);
	scm_c_define_gsubr("init_game_loop", 0, 0, 0, (scm_t_subr) init_game_loop);
	scm_c_define_gsubr("game_loop", 0,0,0, (scm_t_subr) init_game_loop);

	scm_c_define_gsubr("quit",0,0,0, (scm_t_subr) quit);
	scm_c_define_gsubr("add_command", 1, 1, 0, (scm_t_subr) add_command);

	scm_c_define_gsubr("get_next_event", 0,0,0,(scm_t_subr) get_next_event);
	// gge_end read subs

	// gge_begin write subs
	scm_c_export("hello",
			"init_graphics",
			"init_events",
			"init_grid",
			"init_game_loop",
			"game_loop",
			"quit",
			"add_command",
			"get_next_event", NULL);
	// gge_end write subs

	scm_set_current_module(prev_module); // Top module is reset
}
