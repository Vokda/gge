#include "gge_module.hpp"
#include <iostream>
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
