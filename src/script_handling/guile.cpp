#include "guile.hpp"
#include <stdexcept>
#include <string>
#include "gge_api.hpp"
#include <cstdarg>
//#include "../registered_gge_modules.hpp"
#include "guile/gge_api_wrapper.hpp"

Guile::Guile(GGE_API& ga):
	Script_engine(ga)
{
	// handle through config
	//putenv("GUILE_LOAD_PATH=");
	scm_init_guile();

	//scm_c_define_module("gge", NULL);
	add_gge_api_functions();
}

void Guile::read_file(const string& s)
{
	_scm = scm_c_primitive_load(s.c_str());
	// game class should be included by now
	_scm_game_loop = scm_variable_ref(scm_c_lookup("game:game_loop"));
	if(_scm_game_loop == NULL)
	{
		runtime_error re("No game loop procedure set in Guile called 'game_loop'");
		throw re;
	}
}

bool Guile::run_game_loop_once(double delta)
{
	scm_call_1(_scm_game_loop, scm_from_double(delta));
	SCM scm = scm_call_1(_scm_game_loop, scm_from_double(delta));
	bool quit = scm_to_bool(scm);
	return quit;
}

void Guile::add_gge_api_functions()
{
	init_gge_api_wrapper(&_gge_api);

	scm_c_define_gsubr("gge_hello", 0, 0, 0, (scm_t_subr) gge_api_hello);
	// variadic variant that doesn't quite work the entire way
	// scm_c_define_gsubr("gge_init_module", 1, 4, 0, (scm_t_subr) gge_init_module);

	scm_c_define_gsubr("init_graphics", 3, 0, 0, (scm_t_subr) init_graphics);
	scm_c_define_gsubr("init_events", 0, 0, 0, (scm_t_subr) init_events);
	scm_c_define_gsubr("init_grid", 3, 0, 0, (scm_t_subr) init_grid);
	scm_c_define_gsubr("init_game_loop", 0, 0, 0, (scm_t_subr) init_game_loop);
	scm_c_define_gsubr("game_loop", 0,0,0, (scm_t_subr) init_game_loop);

	scm_c_define_gsubr("gge_quit",0,0,0, (scm_t_subr) quit);
	scm_c_define_gsubr("add_command", 1, 1, 0, (scm_t_subr) add_command);

	//scm_c_define_gsubr("gge_init_module", 1, 3, 0, (scm_t_subr) guile_hello);
	//scm_c_export("gge_init_module", NULL);
	//scm_c_define_module("gge api",
}
