#include "gge_api_wrapper.hpp"

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
			case GRAPHICS:
				{
					SCM scm = va_arg(args, SCM);
					char * c = scm_to_locale_string(scm);
					const string s(c);
					free(c);

					scm = va_arg(args, SCM);
					size_t w = scm_to_uint(scm);

					scm = va_arg(args, SCM);
					size_t h = scm_to_uint(scm);

					printf("c string from scheme '%s\n'", c);
					_gge_api->gge_init_module(m, s, w, h);
				}
				break;
			default:
				throw throw_message(__FILE__, "Cannot initialize", m);
		}
	}
} // extern C END

