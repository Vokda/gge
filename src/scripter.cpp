#include "scripter.hpp"
#include <exception>
#include <iostream>
#include <chaiscript/utility/utility.hpp>
#include "initializer.hpp"
#include "core.hpp"
using namespace std;

Scripter::Scripter(const std::string& filename, Initializer& i):
	_initializer(i)
{
	add_defaults();
	try
	{
		cout << "Game file: " << filename << endl;
		auto main_file = _chai.eval_file(filename);
	}
	catch (std::exception& e)
	{
		cerr << e.what() << endl;
	}

}

void Scripter::add_defaults()
{
	chaiscript::ModulePtr m = chaiscript::ModulePtr(new chaiscript::Module());

	chaiscript::utility::add_class<Initializer>(
			*m,
			"Initializer",
			{ chaiscript::constructor<Initializer(Core&)>() },
			{ 
				{chaiscript::fun(&Initializer::graphics), "graphics"},
				{chaiscript::fun(&Initializer::events), "events"}
			});

	_chai.add(chaiscript::var(&_initializer), "__initializer");
	_chai.add(m);
}

/*
template<typename T>
void add_class<T>(std::vector<)
{
	chaiscript::ModulePtr m = chaiscript::ModulePtr(new chaiscript::Module());

	chaiscript::utility::add_class<T>(*m
			T,
			{ chaiscript::constructor<T()>() },
			{ {chaiscript::fun(&T::init_graphics), "init_graphics"} });

	chai.add(m);
}
*/
