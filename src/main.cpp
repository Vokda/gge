#include <iostream>
#include <cstdlib>
#include <csignal>
using namespace std;

#include "script_handling/scripter.hpp"
#include "script_handling/gge_api.hpp"
#include "gge.hpp"  // just a big ascii of "GGE"
#include "core.hpp"
#include "filer.hpp"

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
		// handle path to game given
		Filer filer(argv[1]);

		Core core(filer);
		c = &core; // for signal handling

		GGE_API gge_api(core);
		Scripter scripter(filer, gge_api);

		core.check_modules_initiated();
		core.check_commands_order();

		// signal handling
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
