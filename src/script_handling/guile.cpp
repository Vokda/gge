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
	add_gge_api_functions();
}

void Guile::read_file(const string& s)
{
	_scm = scm_c_primitive_load(s.c_str());
}

void Guile::add_gge_api_functions()
{
	init_gge_api_wrapper(&_gge_api);
	// TODO bind to some variadic (template?) function
	//void (GGE_API::*gge_api_ptr)(rgm module, <...>) = NULL;
	//auto gge_init_ptr = &Guile::gge_init_wrapper;
	//auto gge_hello_ptr = &Guile::gge_hello;

	scm_c_define_gsubr("gge_hello", 0, 0, 0, (scm_t_subr) gge_api_hello);
	scm_c_define_gsubr("gge_init_module", 1, 4, 0, (scm_t_subr) gge_init_module);


	//scm_c_define_gsubr("gge_init_module", 1, 3, 0, (scm_t_subr) guile_hello);
	//scm_c_export("gge_init_module", NULL);
	//scm_c_define_module("gge api",
}
