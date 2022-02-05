/***
 *
 * Class for handling chai objects
 *
 */
#ifndef CHAI_OBJECT_HPP
#define CHAI_OBJECT_HPP

#include <chaiscript/chaiscript.hpp>
#include <string>
#include <vector>
using namespace std;
using namespace chaiscript;

class Chai_object
{
	public:
		Chai_object(ChaiScript& chai, const string& obj_name);
		Chai_object() = delete;

		template<typename R, typename A>
			std::function<R(Boxed_Value&, A)> get_function(const string& fn_name)
			{
				return _chai.eval<std::function<R(chaiscript::Boxed_Value&, A)>>(fn_name);
			}

		void add_function(const string& name);

		const vector<string>& get_fn_names() const {return _member_fn_names;}

		const chaiscript::Boxed_Value& get_boxed_value() const { return _bv; }
		chaiscript::Boxed_Value& get_boxed_value() { return _bv; }
	private:
		ChaiScript& _chai;
		chaiscript::Boxed_Value _bv;
		vector<string> _member_fn_names;
};

#endif
