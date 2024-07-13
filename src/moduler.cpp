#include "moduler.hpp"
#include "gge_modules/gge_module.hpp"
using namespace std;
Moduler::Moduler():
    _logger_info(Logger::get_instance().add_category("Moduler", log4cpp::Priority::INFO))
{
}

int Moduler::list_modules() const
{
    std::stringstream& ss = Logger::get_instance().get_buffer();
	ss << "Loaded modules:" << endl;
	for(auto it = _modules.begin(); it != _modules.end(); ++it)
	{
		ss << "+ " << it->second->get_module_name(it->first) << endl;
	}
	ss << endl;
    _logger_info.info(ss.str());
	return _modules.size();
}

shared_ptr<GGE_module> Moduler::operator[](registered_gge_module m) 
{ 
/*#ifdef DEBUG trying out the unsafe version
	if(_modules[m] == nullptr)
	{
		std::stringstream ss;
		ss << "MODULER: " << "module " << (int)m << " not instantiated" << endl;
        _logger_info.info(ss.str());
		throw runtime_error(ss.str());
	}
#endif*/
	return _modules[m];
}


