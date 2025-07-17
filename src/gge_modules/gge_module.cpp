#include "gge_module.hpp"
#include <sstream>
#include <SDL2/SDL.h>
using namespace std;

GGE_module::GGE_module(rgm m):
    _logger(Logger::get_instance()),
    _log(_logger.add_category(get_module_name(m))),
    _debug_stream(_logger.get_category_stream(get_module_name(m), log4cpp::Priority::DEBUG))
{
	_module = m;
}

GGE_module::GGE_module():
    GGE_module(NONE) // just set to something
{
    _logger.log(get_module_name(_module), log4cpp::Priority::WARN, "WARNING: module type set to NONE that shouldn't be NONE!");
}

GGE_module::GGE_module(const GGE_module& m):
    _logger(m._logger),
    _log(m._log),
    _debug_stream(m._debug_stream)
{
	_module = m._module;
}

rgm GGE_module::get_type()
{
	return _module;
}

const string GGE_module::get_type_string()
{
	return get_module_name(_module);
}

void GGE_module::check_null(const std::string& check_name, const void * SDL_struct)
{
	if(SDL_struct == nullptr)// or *(int*)(SDL_struct) < 0)
	{
		make_and_throw_exception(check_name, SDL_GetError());
	}
	else
	{
	    _ss << check_name<< " - OK" <<endl;;
        _log.info(_ss.str());
	}
}

void GGE_module::check_null(const std::string& check_name, const int SDL_result)
{
	if(SDL_result < 0)
	{
		make_and_throw_exception(check_name, SDL_GetError());
	}
	else
	{
		_log.infoStream() << check_name << " - OK";
	}
}

void GGE_module::make_and_throw_exception(
		const std::string& check_name, 
		const std::string& error)
{
	_ss << check_name << " - SDL Error: " << error << endl;
	std::runtime_error er(_ss.str());
	throw er;
}
