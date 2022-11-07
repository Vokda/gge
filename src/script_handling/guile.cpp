#include "guile.hpp"
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

	// scm_c_define_module("gge", NULL);
	add_gge_api_functions();
	// TODO make it less constant in the future
	_game_loop_str = scm_from_locale_string("game_loop");
}

void Guile::read_file(const string& s)
{
	_scm = scm_c_primitive_load(s.c_str());
}

bool Guile::run_game_loop_once(double delta)
{
	SCM ret = scm_apply_1(_game_loop_str, scm_from_double(delta), NULL);
	return bool(scm_to_bool(ret));
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

	//scm_c_define_gsubr("gge_init_module", 1, 3, 0, (scm_t_subr) guile_hello);
	//scm_c_export("gge_init_module", NULL);
	//scm_c_define_module("gge api",
}
