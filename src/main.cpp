#include "script_handling/scripter.hpp"
#include <iostream>
#include "core.hpp"
#include <cstdlib>
#include "gge.hpp"  // just a big ascii of "GGE"
using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "How to use:" << endl;
		cout << "gge [path/to/game_dir]" << endl;
		exit(1);
	}
	else
	{
		cout << GGE_ASCII << endl;
	}

	// init 
	try
	{
		Core core;
		GGE_API gge_api(core);
		Scripter scripter(argv[1], gge_api);

		core.check_modules_initiated();

		core.run();
	}
	catch (std::exception& e)
	{
		cerr << "FATAL ERROR: " << endl << e.what() << endl;
		// kill all objects
		exit(2);
	}

	cout << "Thanks for using" << endl << GGE_ASCII << endl;
	return 0;
}
