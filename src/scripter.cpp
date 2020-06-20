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
	add_class<Initializer, Core&>(
			"Initializer",
			{ chaiscript::constructor<Initializer(Core&)>() },
			{
				{chaiscript::fun(&Initializer::graphics), "graphics"},
				{chaiscript::fun(&Initializer::events), "events"},
				{chaiscript::fun(&Initializer::grid), "grid"}
			},
			&_initializer,
			"gge_initializer"
			);
}
