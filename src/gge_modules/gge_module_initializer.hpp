#pragma once
#include "gge_module.hpp"
class Script_engine;
class Core;
class Graphics;
class Agenter;
class Events;
namespace gge
{
    class GUI;
}

class GGE_module_initializer
{
	public:
		GGE_module_initializer() = default;

		/*template<typename T, typename... Args>
			shared_ptr<GGE_module> initialize(rgm module, Args... args);*/

		// ye olde C way
		// int rather than rgm to supress warnings regarding varargs
		//shared_ptr<GGE_module> initialize(int module...);

		/* for safe keeping
		shared_ptr<GGE_module> graphics(const string& s, size_t, size_t);
		shared_ptr<GGE_module> events();
		shared_ptr<GGE_module> grid(size_t, size_t, int);
		shared_ptr<GGE_module> game_loop();
		*/

		// gge_begin import ctor_decl
		shared_ptr<GGE_module> graphics(const string& s, size_t, size_t);
		shared_ptr<GGE_module> events(shared_ptr<gge::GUI>);
		shared_ptr<GGE_module> grider(int gt, int width, int height, int tile_size, int x_offset, int y_offset);
		shared_ptr<GGE_module> game_loop(Script_engine&, Core&);
		shared_ptr<GGE_module> none();
		shared_ptr<GGE_module> texter(shared_ptr<Graphics> g);
		shared_ptr<GGE_module> spriter(shared_ptr<Graphics> g);
		shared_ptr<GGE_module> agenter();
		shared_ptr<GGE_module> shaper();
        shared_ptr<GGE_module> gui(shared_ptr<Graphics> g, shared_ptr<Events>);
		// gge_end import ctor_decl
};
