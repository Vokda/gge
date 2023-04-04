#include "gge_module_initializer.hpp"
#include <cstdarg>

// gge_begin import includes
#include "events.hpp"
#include "graphics.hpp"
#include "grider.hpp"
#include "scroller.hpp"
#include "texter.hpp"
#include "game_loop.hpp"
#include "none.hpp"
#include "spriter.hpp"
#include "agenter.hpp"
// gge_end import includes

/*GGE_module_initializer::GGE_module_initializer(Moduler& m):
	_moduler(m)
{
}*/
/*
shared_ptr<GGE_module> GGE_module_initializer::initialize(int module...)
{
	shared_ptr<GGE_module> gge_module = nullptr;
	va_list args;
	va_start(args, module);

	rgm m = static_cast<rgm>(module);
	switch(m)
	{
		case GRAPHICS:
			{
				char* c = va_arg(args, char*);
				string s(c);
				size_t w = va_arg(args, unsigned);
				size_t h = va_arg(args, unsigned);
				gge_module = make_shared<Graphics>(s, w, h);
			}
			break;
		case EVENTS:
			gge_module = make_shared<Events>();
			break;
		case GRID:
			{
				size_t w = va_arg(args, unsigned);
				size_t h = va_arg(args, unsigned);
				int size = va_arg(args, int);
				gge_module = make_shared<Hex_grid>(w, h, size, FLAT_TOP, RECT_ODD_Q);
			}
			break;


				// TODO
		// gge_begin import ctor

		// gge_end import ctor
		default:
			throw throw_message(__FILE__, "Cannot initialize", m);
	}
	return gge_module;
}*/

shared_ptr<GGE_module> GGE_module_initializer::graphics(const string& s, size_t w, size_t h)
{
	return make_shared<Graphics>(s, w, h);
}

shared_ptr<GGE_module> GGE_module_initializer::events()
{
	return make_shared<Events>();
}
shared_ptr<GGE_module> GGE_module_initializer::grider(int gt, int width, int height, int tile_size)
{
	return make_shared<Grider>((grid_type)gt, width, height, tile_size);
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

// gge_begin import ctor_def
// gge_end import ctor_def
