#pragma once
#include <string>
#include "registered_gge_modules.hpp"
#include <memory>
using namespace std;
/*
 * just a small class to have base pointers of modules
 */

class GGE_module
{
	public:
		GGE_module(rgm m);
		GGE_module(const GGE_module& m);
		virtual ~GGE_module() {};

		static string get_module_name(registered_gge_module m)
		{
			switch(m)
			{
				case(NONE):
					return "<no module>";
				// gge_begin cases
				case(GRAPHICS):
					return "Graphics";
				case(EVENTS):
					return "Events";
				case(GRID):
					return "Hex_grid";
				case(SCROLLER):
					return "Scroller";
				case(TEXTER):
					return "Texter";

// gge_end cases
				default:
					return "<Unnamed GGE Module [" + to_string(m) + "]>";
			}
		}

		rgm get_type();
		const string get_type_string();

	protected:
		rgm _module;
};
