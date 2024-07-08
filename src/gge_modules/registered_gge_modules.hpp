#ifndef rgm_hpp
#define rgm_hpp
#include <string>

// modules that are known by gge
enum registered_gge_module {NONE, GRAPHICS, EVENTS, GRIDER, SCROLLER, TEXTER, GAME_LOOP, SPRITER, AGENTER, SHAPER, GUI};
using rgm = registered_gge_module;

typedef registered_gge_module rgm;

// a help function for all the switch cases used with rgm through out the program
const std::string throw_message(const std::string& file_name, const std::string& msg, rgm m);

// gge_begin test parser
/* parser works! */
// gge_end test parser
#endif
