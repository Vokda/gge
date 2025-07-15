#pragma once

#include "script_engine.hpp"
#include <libguile.h>

class Guile: public Script_engine
{
	public:
		Guile(GGE_API& ga);
		void read_file(const string &);
		bool run_game_loop_once(double delta);
        void call_script_fn(void* fn);
	private:
		void add_gge_api_functions();

        struct Call_data 
        {
            SCM fn;
            double delta;
        };

        static SCM call_game_loop(void* data);
        static SCM primitive_load(void*);
        static SCM error_handler(void* data, SCM keys, SCM args);
        static SCM preunwind(void* data, SCM key, SCM params);

		SCM _scm;
		SCM _scm_game_loop;
		SCM _current_module;
};
