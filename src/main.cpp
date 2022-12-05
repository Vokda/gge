#include "script_handling/scripter.hpp"
#include "script_handling/gge_api.hpp"
#include <iostream>
#include "core.hpp"
#include <cstdlib>
#include "gge.hpp"  // just a big ascii of "GGE"
#include <csignal>
using namespace std;

// signal handling
Core* c;
void quit(int sig);


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
		c = &core;

		GGE_API gge_api(core);
		Scripter scripter(argv[1], gge_api);

		core.check_modules_initiated();
		core.check_commands_order();

		signal(SIGINT, quit);
		signal(SIGTERM, quit);
		signal(SIGABRT, quit);

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

void quit(int sig)
{
	c->quit();
}
