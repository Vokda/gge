#include "moduler.hpp"
#include "gge_modules/gge_module.hpp"
#include <iostream>
#ifdef DEBUG
#include <sstream>
#endif
using namespace std;
Moduler::Moduler()
{
}

int Moduler::list_modules() const
{
	cout << "Loaded modules:\n";
	for(auto it = _modules.begin(); it != _modules.end(); ++it)
	{
		cout  << "+ " << it->second->get_module_name(it->first) << endl;
	}
	cout << endl;
	return _modules.size();
}

shared_ptr<GGE_module> Moduler::operator[](registered_gge_module m) 
{ 
#ifdef DEBUG
	if(_modules[m] == nullptr)
	{
		std::stringstream ss;
		ss << "MODULER: " << "module " << (int)m << " not instantiated" << endl;
		throw runtime_error(ss.str());
	}
#endif
	return _modules[m];
}
