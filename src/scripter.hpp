#pragma once
#include <chaiscript/chaiscript.hpp>
//#include <functional>

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
		/* add function
		 * compiles but I'm having some issues with the templates when actually
		 * calling the function
		template<typename R, typename ...Args>
			void add_fn(
					std::function<R(Args...)>& fn,
					const std::string& fn_name)
			{
				_chai.add(chaiscript::fun(&fn), fn_name);
			}
			*/
		//void add_class_fns();
		// add class with functions
		/*template<typename class_added, typename ...Args>
		  void add_class(std::vector<>)
		  { 
			  chaiscript::ModulePtr m = chaiscript::ModulePtr(new chaiscript::Module());

			  chaiscript::utility::add_class<class_added>(
					  *m,
					  "Initializer",
					  { chaiscript::constructor<class_added(Args...)>() },
					  { {chaiscript::fun(&Initializer::graphics), "graphics"} });

			  _chai.add(chaiscript::var(&_initializer), "__initializer");
			  _chai.add(m);
		  }*/
};
