/*
 * Defines the communications between engine and script
 */
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
				  const string& instance_name,
				  bool global
				  )
		  { 
			  chaiscript::utility::add_class<Class>(
					  *_module_ptr,
					  class_name,
					  { chaiscript::constructor<Class(Ctor_args...)>() },
					  member_functions);

			  if(global)
				  _chai.add_global(chaiscript::var(instance), instance_name);
			  else
				  _chai.add(chaiscript::var(instance), instance_name);
		  }
};

#endif
