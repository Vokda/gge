#ifndef SCRIPTER_HPP
#define SCRIPTER_HPP

#include "gge_api.hpp"

#include <chaiscript/chaiscript.hpp>
#include <functional>
using namespace std;

class Initializer;

class Scripter
{
	public:
		Scripter(const string& game_directory, Initializer& i, GGE_API& ga);

	private:
		chaiscript::ChaiScript _chai;
		chaiscript::ModulePtr _module_ptr;

		Initializer& _initializer;
		GGE_API& _gge_api;

		// following function s adds functions and classes to chai script
		// add default functions and variables that gge provides
		void add_defaults(const string& game_dir);

		template<typename Class, typename ...Ctor_args>
		  void add_class(
				  const string& class_name,
				  const vector<chaiscript::Proxy_Function>&& t_constructors,
				  const vector<pair<chaiscript::Proxy_Function, string>>&& member_functions,
				  Class* instance,
				  const string& instance_name
				  )
		  { 
			  chaiscript::ModulePtr m = chaiscript::ModulePtr(new chaiscript::Module());

			  chaiscript::utility::add_class<Class>(
					  *m,
					  class_name,
					  { chaiscript::constructor<Class(Ctor_args...)>() },
					  member_functions);

			  _chai.add(chaiscript::var(instance), instance_name);
			  _chai.add(m);
		  }
};

#endif
