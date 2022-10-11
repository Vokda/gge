#include "guile.hpp"
#include <cstdlib>
#include "gge_api.hpp"

Guile::Guile()
{
	// handle through config
	//putenv("GUILE_LOAD_PATH=");
	scm_init_guile();
}

void Guile::read_file(const char* c)
{
	_scm = scm_c_primitive_load(c);
}

void Guile::add_std_modules()
{
	// TODO bind to some variadic (template?) function
	scm_c_define_gsubr("gge_init_module", 1, 3, 0, &);
}
