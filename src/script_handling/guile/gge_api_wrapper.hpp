// C-wrappers necessary for guile
#pragma once
#include "../gge_api.hpp"
#include <libguile.h>
#include <string>

extern "C"
{ 
	static GGE_API* _gge_api = NULL;
	void init_gge_api_wrapper(GGE_API* ga);

	void gge_api_hello();
	void gge_init_module(SCM module...);

}
