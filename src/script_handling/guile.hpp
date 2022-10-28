#pragma once

#include "script_engine.hpp"
#include <libguile.h>

class Guile: public Script_engine
{
	public:
		Guile(GGE_API& ga);
		void read_file(const string &);
	private:
		void add_gge_api_functions();

		// wrapper functions
		SCM gge_hello();
		static SCM gge_init_wrapper(SCM module, ...);

		SCM _scm;
};
