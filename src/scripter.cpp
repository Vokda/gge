#include "scripter.hpp"
#include <exception>
#include <iostream>
using namespace std;

Scripter::Scripter(const std::string& filename)
{
	try
	{
		cout << filename << endl;
		_chai.eval_file(filename);
	}
	catch (std::exception& e)
	{
		;
	}

}
