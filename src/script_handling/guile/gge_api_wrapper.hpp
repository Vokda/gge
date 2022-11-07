// C-wrappers necessary for guile
#pragma once
#include "../gge_api.hpp"
#include <libguile.h>

extern "C"
{ 
	static GGE_API* _gge_api = NULL;
	void init_gge_api_wrapper(GGE_API* ga);

	void gge_api_hello();
	//void gge_init_module(SCM module...);

	// init
	void init_graphics(SCM string, SCM w, SCM h);
	void init_events();
	void init_grid(SCM w, SCM h, SCM size);
	void init_game_loop();

	//void add_command()
}
