#pragma once
#include <chaiscript/chaiscript.hpp>
#include <functional>

class Initializer;

class Scripter
{
	public:
		Scripter(const std::string& filename, Initializer& i);

	private:
		chaiscript::ChaiScript _chai;
		chaiscript::ModulePtr _module_ptr;

		Initializer& _initializer;

		// following function s adds functions and classes to chai script
		// add default functions that gge provides
		void add_defaults();

		template<typename Class, typename ...Ctor_args>
		  void add_class(
				  const std::string& class_name,
				  const std::vector<chaiscript::Proxy_Function>&& t_constructors,
				  const std::vector<
				  std::pair<chaiscript::Proxy_Function, std::string>
				  >&& member_functions,
				  Class* instance,
				  const std::string& instance_name
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
