#include "game_loop_command.hpp"
#include "../game_loop.hpp"

Game_loop_command::Game_loop_command(
				std::shared_ptr<Game_loop> gm, 
				std::shared_ptr<GGE_module> command_arg, // should be None
				double& arg // should NOT be None
				): 
	Command(gm, command_arg), // special case for game loop where arg is NOT stored in Command class TODO see manual
	_arg(arg)
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
