#include "game_loop.hpp"
#include <iostream>
using namespace std;

Game_loop::Game_loop(Script_engine& se, Core& c):
	GGE_module(GAME_LOOP), _script_engine(se), _core(c)
{
	cout << "Game_loop - OK" << endl;
}
	

void Game_loop::tick(double d)
{
	// quit if false is returned from game loop
	if(!_script_engine.run_game_loop_once(d))
	{
		_core.quit();
	}
}
