#pragma once
#include <string>
#include "registered_gge_modules.hpp"
using namespace std;
/*
 * just a small class to have base pointers of modules
 */

class GGE_module
{
	public:
		virtual ~GGE_module() = default;

		static string get_module_name(registered_gge_module m)
		{
			switch(m)
			{
				// gge_begin cases
				case(GRAPHICS):
					return "Graphics";
				case(EVENTS):
					return "Events";
				case(GRID):
					return "Grid";
				// gge_end cases
				default:
					return "<Unnamed GGE Module [" + to_string(m) + "]>";
			}
		}
	private:
};
