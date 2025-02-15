#pragma once
#include "gge_module.hpp"
/*class Script_engine;
class Core;
class Graphics;
class Agenter;
class Events;
class GGE_API;*/

#include "scroller.hpp"
#include "events.hpp"
#include "graphics.hpp"
#include "grider.hpp"
#include "scroller.hpp"
#include "texter.hpp"
#include "game_loop.hpp"
#include "none.hpp"
#include "spriter.hpp"
#include "agenter.hpp"
#include "shaper.hpp"
#include "gui.hpp"

/*namespace gge
{
    class GUI;
}*/
#include "../logger.hpp"

class GGE_module_initializer
{
	public:
		GGE_module_initializer();;

		template<typename T, typename... Args>
			shared_ptr<GGE_module> initialize(Args&&... args)
            {
                _log.info("Creating");
                _log.info(typeid(T).name());
                return make_shared<T>(args...);
            };

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
        shared_ptr<GGE_module> gui(shared_ptr<Graphics> g, shared_ptr<Events>, GGE_API&);
		// gge_end import ctor_decl

    private:
        Logger::Log& _log;
        Logger::Log_stream _log_stream;
};
