#include "guile.hpp"
#include <stdexcept>
#include <string>
#include "gge_api.hpp"
#include <cstdarg>
//#include "../registered_gge_modules.hpp"
#include "guile/gge_api_wrapper.hpp"

static Guile* guile;

Guile::Guile(GGE_API& ga):
	Script_engine(ga)
{
	guile = this;
	// handle through config
	//putenv("GUILE_LOAD_PATH=");
	scm_init_guile(); //not cross platform compatible
	char arg1[] = "--debug";
	char *argv = arg1;
	//scm_boot_guile(1, &argv, guile_main, 0); 
	//scm_with_guile(&guile_main, NULL);
	scm_set_program_arguments(1, &argv, NULL);
	add_gge_api_functions();
}

void Guile::read_file(const string& s)
{
	_scm = scm_c_primitive_load(s.c_str());
	// game class should be included by now
	SCM game_module = scm_c_resolve_module("game");
	SCM game_loop_fn = scm_c_module_lookup(game_module, "game_loop");
	_scm_game_loop = scm_variable_ref(game_loop_fn);
	//_scm_game_loop = scm_variable_ref(scm_c_lookup("game:game_loop"));
	if(_scm_game_loop == NULL)
	{
		runtime_error re("No game loop procedure set in Guile called 'game_loop'");
		throw re;
	}
}

bool Guile::run_game_loop_once(double delta)
{
	SCM scm = scm_call_1(_scm_game_loop, scm_from_double(delta));
	bool quit = scm_to_bool(scm);
	return quit;
}

void Guile::call_script_fn(void* fn)
{
    call_function((SCM)fn);
}

void Guile::add_gge_api_functions()
{
	init_gge_api_wrapper(&_gge_api);

	SCM current_module = scm_c_define_module("gge", NULL, NULL);
	SCM prev_module = scm_set_current_module(current_module);

	// gge_begin read subs
	// scm_c_define_gsubr ( name, required, optional, rest, function)
	scm_c_define_gsubr("hello", 0, 0, 0, (scm_t_subr) gge_api_hello);

	scm_c_define_gsubr("init_graphics", 3, 0, 0, (scm_t_subr) init_graphics);
	scm_c_define_gsubr("init_events", 0, 0, 0, (scm_t_subr) init_events);
	scm_c_define_gsubr("init_grider", 6, 0, 0, (scm_t_subr) init_grider);
	scm_c_define_gsubr("init_game_loop", 0, 0, 0, (scm_t_subr) init_game_loop);
	scm_c_define_gsubr("init_texter", 0, 0, 0, (scm_t_subr) init_texter);
	scm_c_define_gsubr("init_spriter", 0, 0, 0, (scm_t_subr) init_spriter);
	scm_c_define_gsubr("init_agenter", 0, 0, 0, (scm_t_subr) init_agenter);
	scm_c_define_gsubr("init_gui", 0, 0, 0, (scm_t_subr) init_gui);

	scm_c_define_gsubr("game_loop", 0,0,0, (scm_t_subr) init_game_loop);

	scm_c_define_gsubr("quit",0,0,0, (scm_t_subr) quit);
	scm_c_define_gsubr("add_command", 1, 2, 0, (scm_t_subr) add_command);

	scm_c_define_gsubr("get_next_event", 0,0,0,(scm_t_subr) get_next_event);

	scm_c_define_gsubr("create_text", 5,0,0, (scm_t_subr) create_text);

	scm_c_define_gsubr("set_tile_color", 4,0,0, (scm_t_subr) set_tile_color);
	scm_c_define_gsubr("get_tile_from_mouse", 2,0,0, (scm_t_subr) get_tile_from_mouse);
	scm_c_define_gsubr("get_mouse_position", 0,0,0, (scm_t_subr) get_mouse_position);

	scm_c_define_gsubr("set_tile_custom_data", 3,0,0, (scm_t_subr) set_tile_custom_data);
	scm_c_define_gsubr("get_tile_custom_data", 2,0,0, (scm_t_subr) get_tile_custom_data);

	scm_c_define_gsubr("load_image", 1,0,0, (scm_t_subr) load_image);
	scm_c_define_gsubr("create_sprite", 3,0,0, (scm_t_subr) create_sprite);

	scm_c_define_gsubr("create_agent", 2,0,0, (scm_t_subr) create_agent);
	scm_c_define_gsubr("get_agents", 0,1,1, (scm_t_subr) get_agents);
	scm_c_define_gsubr("move_agent", 2,0,0, (scm_t_subr) move_agent);
	scm_c_define_gsubr("remove_agent", 1,0,0, (scm_t_subr) remove_agent);
	scm_c_define_gsubr("change_agent_sprite", 2,0,0, (scm_t_subr) change_agent_sprite);

    // gui
	scm_c_define_gsubr("create_button", 2,0,0, (scm_t_subr) create_button);


	// gge_end read subs

	// gge_begin write subs
	scm_c_export("hello",
			"init_graphics",
			"init_events",
			"init_grider",
			"init_game_loop",
			"init_agenter",
            "init_gui",
			"game_loop",
			"quit",
			"add_command",
			"get_next_event", 
			"init_texter",
			"init_spriter",
			"create_text",
			"get_mouse_position",
			"get_tile_from_mouse",
			"set_tile_color",
			"set_tile_custom_data",
			"get_tile_custom_data", 
			"load_image",
			"create_sprite",
			"create_agent",
			"move_sprite",
			"remove_sprite",
			"get_agents",
			"move_agent",
			"remove_agent",
			"change_agent_sprite",
            "create_button",
			NULL);
	// gge_end write subs

	scm_set_current_module(prev_module); // Top module is reset
}
