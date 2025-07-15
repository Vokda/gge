#include "gge_api_wrapper.hpp"
#include <string>
#include <vector>
#include <cstdarg>
#include <iostream>
#include <sstream>
#include <variant>
#include <tuple>
#include <algorithm>
using namespace std;
#include "../gge_api.hpp"

extern "C"
{
	static GGE_API* _gge_api;

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
		va_list args ;
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

	SCM init_grider(SCM gt, SCM w, SCM h, SCM s, SCM x_offset, SCM y_offset)
	{
		return scm_from_int(
				_gge_api->init_grider(
					scm_to_int(gt),
					scm_to_int(w),
					scm_to_int(h),
					scm_to_int(s),
					scm_to_int(x_offset),
					scm_to_int(y_offset)
					)
				);
	}

	SCM init_game_loop()
	{
		return scm_from_int(
				_gge_api->init_game_loop()
				);


	}

	SCM add_command(SCM module, SCM command, SCM applied_to_module)
	{
        int module_id = scm_to_int(module);
        int cmd = scm_to_int(command);
        int module_id_applied = scm_to_int(applied_to_module);

        _gge_api->add_command(
                (rgm)module_id,
                cmd,
                (rgm)module_id_applied
                );
        return SCM_UNSPECIFIED;
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

	SCM init_agenter()
	{
		return scm_from_int(
				_gge_api->init_agenter()
				);
	}
	
	SCM init_spriter()
	{
		return scm_from_int(
				_gge_api->init_spriter()
				);
	}

    SCM init_gui()
    {
        return scm_from_int(
                _gge_api->init_gui()
                );
    }

	SCM create_text(SCM text, SCM scm_x, SCM scm_y, SCM ms, SCM view_port)
	{
		const char* c = scm_to_locale_string(text);
		// TODO add dynamic wind to free up memory
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


	SCM get_tile_from_mouse(SCM x, SCM y)
	{
		return scm_from_int(
				_gge_api->get_tile_from_mouse(
					scm_to_int(x),
					scm_to_int(y)
					));
	}

	SCM get_mouse_position()
	{
		std::vector<int> mp = _gge_api->get_mouse_position();
		return scm_list_2(scm_from_int(mp[0]), scm_from_int(mp[1]));
	}

	void set_tile_custom_data(SCM index, SCM name, SCM data)
	{
		int i = scm_to_int(index);
		const char *c = scm_to_locale_string(name);
		const string str(c);
		void* d = scm_to_pointer(data);
		_gge_api->set_tile_custom_data(i, str, d);
	}

	SCM get_tile_custom_data(SCM index, SCM name)
	{
		int i = scm_to_int(index);
		const char *c = scm_to_locale_string(name);
		const string str(c);
		return scm_from_pointer( _gge_api->get_tile_custom_data(i, str), NULL );
	}

	SCM load_image(SCM path)
	{
		const char *c = scm_to_locale_string(path);
		const string str(c);
		return scm_from_int(_gge_api->load_image(str));
	}

	SCM create_sprite(SCM texture, SCM x, SCM y)
	{
		return scm_from_int(
				_gge_api->create_sprite(
					scm_to_int(texture),
					scm_to_int(x),
					scm_to_int(y)
					));
	}

    SCM create_agent(SCM sprite, SCM tile)
    {
        return scm_from_int(
                _gge_api->create_agent(
                    scm_to_int(sprite),
                    scm_to_int(tile)
                    ));
    }

    void change_agent_sprite(SCM agent, SCM texture)
    {
        _gge_api->change_agent_sprite(scm_to_int(agent), scm_to_int(texture));
    }

} // extern C END

template<typename... T>
std::tuple<T...> unpack_to_tuple(const vector<std::variant<T...>>& variant_parameters)
{
    std::tuple<T...> result;

    //auto it = std::begin(variant_parameters);
    _log.debug("variant parameters size %i", variant_parameters.size());
    for(const auto& vp: variant_parameters)
    {
        //_log.debug(std::visit(vp));
        std::visit([result](auto&& v){
                _log.debug("value %i", v);
                std::tuple_cat(result, std::make_tuple(v));
                }, vp);
    }


    /*std::apply([&](auto&... args) {
                ( (args = std::get< std::decay_t< decltype(args) > >(*it++)), ...);
            }, 
            result);*/
    return result;
}

SCM initialize_gge_module(SCM scm_module, SCM scm_args...)
{
    // unpack arguments
    va_list args;
    va_start(args, scm_args);

    // first parameter should be module nr TODO rgm
    int module = -1;
    _log.info(__FUNCTION__);
    if(scm_module == SCM_UNDEFINED)
        throw runtime_error("undefined");
    if(scm_is_integer(scm_module))
        module = scm_to_int(scm_module); 
    else
        _log.fatal("gge module requested to initizlize not an integer");

    if(module == -1)
        throw runtime_error("module not set!");
    else
        _log.info("Requesting initialization of module %i ", module);

    //get rest of parameters
    using scm_union = std::variant<int, double, std::string>;
    std::vector<scm_union> parameters;

    while(SCM scm = va_arg(args, SCM))
    {
        if(scm_is_integer(scm))
        {
            parameters.push_back(scm_to_int(scm));
        }
        else if(scm_is_real(scm))
        {
            parameters.push_back(scm_to_double(scm));
        }
        else if(scm_is_string(scm))
        {
            const char* c = scm_to_locale_string(scm);
            const string str(c);
            parameters.push_back(str);
        }
        else
        {
            //throw runtime_error("Type not supported");
            break; // probably null?
        }
    }
    va_end(args);

    // call gge api
    auto tuple_parameters = unpack_to_tuple(parameters);
//(module, tuple_parameters),
    int module_id = -1; 
    /*module = std::apply(
                [&](auto&&... args) { 
                    return _gge_api->initialize_gge_module(module, 
                            std::forward<decltype(args)>(args)...); 
                    },
                tuple_parameters
            );*/
    _log_stream << typeid(tuple_parameters).name() ;

    return scm_from_int(module_id);
}

SCM move_agent(SCM agent, SCM tile)
{
	return scm_from_bool(
            _gge_api->move_agent(
                scm_to_int(agent),
                scm_to_int(tile)
                ));
}

void remove_agent(SCM agent)
{
	_gge_api->remove_agent(scm_to_int(agent));
}
					

SCM get_agents(SCM tile)
{
	const vector<int> agents = _gge_api->get_agents((scm_null_p(tile)) ?	scm_to_int(tile) : -1);
	if(agents.size() > 0)
		return make_list(&agents[0], agents.size());
	else
		return scm_list_n(SCM_UNDEFINED);
}

SCM make_list(const int* agents, size_t size)
{
	if(size > 0)
	{
		int agent = *agents;
		return scm_cons(scm_from_int(agent), make_list(++agents, --size));
	}
	else
	{
		return scm_list_n(SCM_UNDEFINED);
	}
}

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

void set_tile_color(SCM r, SCM g, SCM b, SCM index)
{
	int i = scm_to_int(index);
	if(i < 0) return;
	if(!scm_is_integer(r))
	{
		int red = scm_to_int(r);
		stringstream ss;
		ss << "not an int " << red << endl;
		ss << "scm_is_integer(r) "<< scm_is_integer(r) << endl;
		throw runtime_error(ss.str());
	}
	else
	{
		_gge_api->set_tile_color(
				{scm_to_int(r), scm_to_int(g),scm_to_int(b)},
				i);
		cout << ""; // TODO not having a cout here causes a segfault
	}
}

SCM get_neighbors(SCM tile)
{
	int t = scm_to_int(tile);
	return vector_to_list(_gge_api->get_neighbors(t));
}

SCM create_button(SCM text, SCM fn)
{
    if(!scm_is_true(scm_procedure_p(fn)))
        throw runtime_error("Not a procedure!");
    return scm_from_int(
            _gge_api->create_button(
                scm_to_string(text),
                (void*)fn
                )
            );
}

void call_function(SCM fn)
{
    scm_call_0(fn);
}

const string scm_to_string(SCM text)
{
    const char* c = scm_to_locale_string(text);
    const string scm_str(c);
    return scm_str;
}
