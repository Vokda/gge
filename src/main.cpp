#include <iostream>
#include <sstream>
#include <cstdlib>
#include <csignal>
using namespace std;

#include "script_handling/scripter.hpp"
#include "script_handling/gge_api.hpp"
#include "gge.hpp"  // just a big ascii of "GGE"
#include "core.hpp"
#include "filer.hpp"
#include "configurer.hpp"
#include "logger.hpp"

// signal handling
Core* c;
void quit(int sig);


int main(int argc, char* argv[])
{
    Logger& logger = Logger::get_instance();
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
        logger.info("GGE booting");

		// TODO add class to handle arguments properly
		// Argument handler here
		// handle path to game given
		Filer game_path(argv[1]);


		// TODO make argument changeable (2nd arg)
        // TODO 2nd arg was 1 but no constructor defnied for it; dafuq?
		Core core(game_path);
		c = &core; // for signal handling

		GGE_API gge_api(core);
		Configurer configurer(game_path, gge_api);
		Scripter scripter(game_path, gge_api, configurer.get_configuration());

		core.check_modules_initiated();
		core.check_commands_order();

		// signal handling
		signal(SIGINT, quit);
		signal(SIGTERM, quit);
		signal(SIGABRT, quit);

        logger.info("GGE running");
		core.run();
	}
	catch (std::exception& e)
	{
        stringstream ss;
        ss << e.what() << endl << "EXITING GGE" << endl;
        logger.fatal(ss.str());
		//cerr << ss.str();
		// kill all objects
		exit(2);
	}

	logger.info("Thanks for using\n" + std::string(GGE_ASCII));
    logger.info("GGE exiting normally");
	return 0;
}

void quit(int sig)
{
	c->quit();
}
