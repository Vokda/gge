#include "chai_object.hpp"

Chai_object::Chai_object(ChaiScript& chai, const string& obj_name):
	_chai(chai)
{
	_bv = chai.eval(obj_name);
}


void Chai_object::add_function(const string& name)
{
	_member_fn_names.push_back(name);
}
