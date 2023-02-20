#include "registered_gge_modules.hpp"
#include <sstream>
#include "gge_module.hpp"

const std::string throw_message(const std::string& file_name, const std::string& msg, rgm m)
{
	std::stringstream ss;
	ss << file_name << ": " << msg << ": " << GGE_module::get_module_name(m) << std::endl;
	return ss.str();
}
