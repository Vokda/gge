#include "gge_api_wrapper.hpp"
#include <string>
#include <vector>

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
					-1,
					(rgm)-1
					);
		}
		else // assume there might be an arg
		{
			int cmd = scm_to_int(scm); 
			scm = va_arg(args, SCM);
			if(scm == NULL)
			{
				_gge_api->add_command(
						(rgm)scm_to_int(module),
						cmd,
						(rgm)-1
						);
			}
			else
			{
				_gge_api->add_command(
						(rgm)scm_to_int(module),
						cmd,
						(rgm)scm_to_int(scm)
						);
			}
			va_end(args);
		}
	}

	void quit()
	{
		_gge_api->quit();
	}

	SCM get_next_event()
	{
		int event = _gge_api->pop_event();
		return scm_from_int(event);
	}

	SCM init_texter()
	{
		return scm_from_int(
				_gge_api->init_texter()
				);
	}

	SCM create_text(SCM text, SCM scm_x, SCM scm_y, SCM ms, SCM view_port)
	{
		const char* c = scm_to_locale_string(text);
		const string str(c);
		int x = scm_to_int(scm_x);
		int y = scm_to_int(scm_y);

		return scm_from_uint(
				_gge_api->create_text(
					str,
					{255,255,255,255},
					{x,y,-1,-1},
					scm_to_int(ms),
					scm_to_int(view_port)
					)
				);
	}

	void set_hex_color(SCM r, SCM g, SCM b, SCM index)
	{
		int i = scm_to_int(index);
		if(i < 0) return;
		_gge_api->set_hex_color(
				{scm_to_int(r), scm_to_int(g),scm_to_int(b),},
				i);
	}

	SCM get_hex_from_mouse(SCM x, SCM y)
	{
		return scm_from_int(
				_gge_api->get_hex_from_mouse(
					scm_to_int(x),
					scm_to_int(y)
					));
	}

	SCM get_mouse_position()
	{
		std::vector<int> mp = _gge_api->get_mouse_position();
		return scm_list_2(scm_from_int(mp[0]), scm_from_int(mp[1]));
	}

	void set_hex_custom_data(SCM index, SCM name, SCM data)
	{
		int i = scm_to_int(index);
		const char *c = scm_to_locale_string(name);
		const string str(c);
		void* d = scm_to_pointer(data);
		_gge_api->set_hex_custom_data(i, str, d);
	}

	SCM get_hex_custom_data(SCM index, SCM name)
	{
		int i = scm_to_int(index);
		const char *c = scm_to_locale_string(name);
		const string str(c);
		return scm_from_pointer( _gge_api->get_hex_custom_data(i, str), NULL );
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
