#include "gge_module_initializer.hpp"
#include <cstdarg>

// gge_begin import includes
/*#include "events.hpp"
#include "graphics.hpp"
#include "grider.hpp"
#include "scroller.hpp"
#include "texter.hpp"
#include "game_loop.hpp"
#include "none.hpp"
#include "spriter.hpp"
#include "agenter.hpp"
#include "shaper.hpp"
#include "gui.hpp"*/
#include "../script_handling/gge_api.hpp"
// gge_end import includes

GGE_module_initializer::GGE_module_initializer():
    _log(Logger::make_category("GGE Module Initializer")),
    _log_stream(Logger::make_category_stream(Priority::INFO, "GGE Module Initializer"))
{
    _log.info("Initializer initialized");
}

shared_ptr<GGE_module> GGE_module_initializer::graphics(const string& s, size_t w, size_t h)
{
	return make_shared<Graphics>(s, w, h);
}

shared_ptr<GGE_module> GGE_module_initializer::events(shared_ptr<gge::GUI> gui)
{
	return make_shared<Events>(gui);
}
shared_ptr<GGE_module> GGE_module_initializer::grider(int gt, int width, int height, int tile_size, int x_offset, int y_offset)
{
	return make_shared<Grider>((grid_type)gt, width, height, tile_size, x_offset, y_offset);
}

shared_ptr<GGE_module> GGE_module_initializer::game_loop(Script_engine& se, Core& c)
{
	return make_shared<Game_loop>(se, c);
}

shared_ptr<GGE_module> GGE_module_initializer::none()
{
	return make_shared<None>();
}

shared_ptr<GGE_module> GGE_module_initializer::texter(shared_ptr<Graphics> g)
{
	return make_shared<Texter>(g);
}

shared_ptr<GGE_module> GGE_module_initializer::spriter(shared_ptr<Graphics> g)
{
	return make_shared<Spriter>(g);
}

shared_ptr<GGE_module> GGE_module_initializer::agenter()
{
	return make_shared<Agenter>();
}

shared_ptr<GGE_module> GGE_module_initializer::shaper()
{
	return make_shared<Shaper>();
}

shared_ptr<GGE_module> GGE_module_initializer::gui(shared_ptr<Graphics> g, shared_ptr<Events> events, GGE_API& gge_api)
{
    auto gui = make_shared<gge::GUI>(g->get_window(), g->get_renderer(), gge_api);
    events->set_gui(gui);
	return gui;
}

template<>
shared_ptr<GGE_module> GGE_module_initializer::init_gge_module<Agenter>()
{
    _log.info("Creating agenter");
    return make_shared<Agenter>();
};

// gge_begin import ctor_def
// gge_end import ctor_def
