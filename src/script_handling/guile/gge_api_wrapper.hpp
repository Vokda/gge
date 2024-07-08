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
	SCM init_graphics(SCM string, SCM w, SCM h);
	SCM init_events();
	SCM init_grider(SCM gt, SCM w, SCM h, SCM size, SCM x, SCM y);
	SCM init_game_loop();
	SCM init_texter();
	SCM init_spriter();
	SCM init_agenter();
    SCM init_gui();

	void add_command(SCM module...);

	void quit();

	//SCM create_text(SCM text, SCM view_port);
	SCM create_text(
			SCM text, 
			/* TODO color */
			SCM x,
			SCM y,
			/* TODO size */
			SCM ms,
			SCM view_port
			);

	SCM get_next_event();

	void set_tile_color(SCM r, SCM g, SCM b, SCM index);

	SCM get_tile_from_mouse(SCM x, SCM y);
	SCM get_neighbors(SCM tile);

	SCM get_mouse_position();

	void set_tile_custom_data(SCM i, SCM name, SCM data);
	SCM get_tile_custom_data(SCM index, SCM name);

	SCM load_image(SCM path);
	SCM create_sprite(SCM texture, SCM x, SCM y);

	// agents
	SCM create_agent(SCM sprite, SCM tile);
	SCM get_agents(SCM tile);
	void move_agent(SCM agent, SCM tile);
	void remove_agent(SCM agent);
	void change_agent_sprite(SCM agent, SCM texture);

// privates
	SCM make_list(const int* e, size_t s);
}
	template<typename T>
SCM vector_to_list(const vector<T>& v)
{
	if(v.size() > 0)
		return make_list(&v[0], v.size());
	else
		return scm_list_n(SCM_UNDEFINED);
}
