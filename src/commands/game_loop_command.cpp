#include "game_loop_command.hpp"
#include "../game_loop.hpp"

Game_loop_command::Game_loop_command(
				std::shared_ptr<Game_loop> gm, 
				double& arg
				): _arg(arg)
{
	_game_loop = gm;
}

void Game_loop_command::execute()
{
	_game_loop->tick(_arg);
}

const string Game_loop_command::get_command_string() const
{
	return "_game_loop->tick(delta)";
}
