#include "gge_api_wrapper.hpp"
#include <string>

extern "C"
{
	extern GGE_API* _gge_api;

	void init_gge_api_wrapper(GGE_API* ga)
	{
		_gge_api = ga;
	}

	void gge_api_hello()
	{
		_gge_api->hello();
	}

	void gge_init_module(SCM module...)
	{
		va_list(args);
		va_start(args, module);
		rgm m = static_cast<rgm>(scm_to_int(module));
		switch(m)
		{
//#include "guile_init_module_switch.generated"
			default:
				throw throw_message(__FILE__, "Cannot initialize", m);
		}
	}


	void init_events()
	{
		_gge_api->init_events();
	}

	void init_grid(SCM w, SCM h, SCM s)
	{
		_gge_api->init_grid(
				scm_to_uint(w),
				scm_to_uint(h),
				scm_to_int(s)
				);
	}

	void init_game_loop()
	{
		_gge_api->init_game_loop();
	}

} // extern C END

// definition outside to handle C++ strings
void init_graphics(SCM s, SCM w, SCM h)
{
	const char* c = scm_to_locale_string(s);
	const string str(c);

	_gge_api->init_graphics(str, 
			scm_to_uint(w),
			scm_to_uint(h)
			);
}
