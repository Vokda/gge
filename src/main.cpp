#include "scripter.hpp"
#include <iostream>
#include "core.hpp"
#include "gge_api.hpp"
#include "initializer.hpp"
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "Please provide a game file (.chai)" << endl;
		exit(1);
	}

	// init 
	try
	{
		Core core;
		Initializer initializer(core);
		GGE_API gge_api(core);
		Scripter scripter(argv[1], initializer, gge_api);

		core.check_modules_initiated();

		core.run();
	}
	catch (std::exception& e)
	{
		cerr << "FATAL ERROR: " << endl << e.what() << endl;
		// kill all objects
		exit(2);
	}

	cout << "Thanks for playing!" << endl;
	return 0;
}
