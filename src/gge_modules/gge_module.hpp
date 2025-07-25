#pragma once
#include <string>
#include "registered_gge_modules.hpp"
#include <memory>
#include "../logger.hpp"
using namespace std;
/*
 * just a small class to have base pointers of modules
 */

class GGE_module
{
	public:
		GGE_module(rgm m);
		GGE_module();
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
				case(GRIDER):
					return "Grider";
				case(SCROLLER):
					return "Scroller";
				case(TEXTER):
					return "Texter";
				case(GAME_LOOP):
					return "Game_loop";
				case(SPRITER):
					return "Spriter";
				case(AGENTER):
					return "Agenter";
                case(SHAPER):
                    return "Shaper";
                case(GUI):
                    return "GUI";
					// gge_end cases
				default:
                    {
                        string s = "Unnamed GGE Module [" + to_string(m) + "]";
                        auto& log = Logger::make_category("NONE");
                        log.warn(s);
                        //Logger::get_instance().log("NONE", , s);
                        return "<" + s + ">";
                    }
			}
		}

		rgm get_type();
		const string get_type_string();

	protected:
		rgm _module;
        Logger& _logger;
        Logger::Log& _log;
        Logger::Log_stream _debug_stream;
};
