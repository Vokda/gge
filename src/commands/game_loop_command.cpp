#include "game_loop_command.hpp"

Game_loop_command::Game_loop_command(
				std::shared_ptr<GGE_module> m, 
				std::shared_ptr<GGE_module> arg,
				command cmd
				):
	Command(m, arg, cmd)
{
	_game_loop = static_pointer_cast<Game_loop>(m);
}

void Game_loop_command::execute()
{
	throw "Game loop error";
}

void Game_loop_command::execute(double d)
{
	_game_loop->tick(d);
}
