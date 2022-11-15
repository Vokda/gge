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

	SCM init_events()
	{
		return scm_from_int(
			_gge_api->init_events()
			);
	}

	SCM init_grid(SCM w, SCM h, SCM s)
	{
		return scm_from_int(
				_gge_api->init_grid(
					scm_to_uint(w),
					scm_to_uint(h),
					scm_to_int(s)
					)
				);
	}

	SCM init_game_loop()
	{
		return scm_from_int(
				_gge_api->init_game_loop()
				);


	}

	void add_command(SCM module...)
	{
		va_list args;
		va_start(args, module);
		SCM scm = va_arg(args, SCM);
		if(scm == NULL)
		{
			va_end(args);
			_gge_api->add_command(
					(rgm)scm_to_int(module),
					-1
					);
		}
		else
		{
			va_end(args);
			_gge_api->add_command(
					(rgm)scm_to_int(module),
					scm_to_int(scm)
					);
		}
	}

	void quit()
	{
		_gge_api->quit();
	}

} // extern C END

// definition outside to handle C++ strings
SCM init_graphics(SCM s, SCM w, SCM h)
{
	const char* c = scm_to_locale_string(s);
	const string str(c);

	return scm_from_int(
			_gge_api->init_graphics(str, 
				scm_to_uint(w),
				scm_to_uint(h)
				)
			);
}
