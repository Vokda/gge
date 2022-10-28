#include "registered_gge_modules.hpp"
#include <sstream>
const std::string throw_message(const std::string& file_name, const std::string& msg, rgm m)
{
	std::stringstream ss(file_name);
	ss << ": " << msg << ": " << m << std::endl;
	return ss.str();
}
