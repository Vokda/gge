#include "gge_module.hpp"
#include <iostream>
using namespace std;

GGE_module::GGE_module(rgm m)
{
	if(m == NONE)
	{
		cerr << "WARNING: module type set to NONE!" << endl;
	}
	_module = m;
}

GGE_module::GGE_module(const GGE_module& m)
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

