#pragma once

#include <string>
#include <sstream>

#include "gge_module.hpp"

// gge_begin includes
#include "events.hpp"
#include "graphics.hpp"
#include "hex/hex_grid.hpp"
#include "scroller.hpp"
#include "texter.hpp"
#include "hex/orientation.hpp"
// gge_end includes

class GGE_module_initializer
{
	public:
		GGE_module_initializer() = default;

		template<typename... Args>
			shared_ptr<GGE_module> initialize(rgm module, Args... args)
			{
				switch(module)
				{
					//gge_begin set_modules
					case(GRAPHICS):
						return make_shared<Graphics>(args...);
						break;
					//gge_end set_modules
					default:
						stringstream s;
						s << __FILE__ << ": Cannot initialize " << GGE_module::get_module_name(module);
						throw s;
						break;
				}
			}
};
