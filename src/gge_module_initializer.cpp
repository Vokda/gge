#include "gge_module_initializer.hpp"
#include <cstdarg>

// gge_begin import includes
#include "events.hpp"
#include "graphics.hpp"
#include "hex/hex_grid.hpp"
#include "scroller.hpp"
#include "texter.hpp"
#include "hex/orientation.hpp"
#include "game_loop.hpp"
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
shared_ptr<GGE_module> GGE_module_initializer::grid(size_t w, size_t h, int s)
{
	// TODO the last two arguments need to be parameterizable
	return make_shared<Hex_grid>(w, h, s, FLAT_TOP, RECT_ODD_Q);
}

shared_ptr<GGE_module> GGE_module_initializer::game_loop(Script_engine& se, Core& c)
{
	return make_shared<Game_loop>(se, c);
}

// gge_begin import ctor_def
// gge_end import ctor_def
