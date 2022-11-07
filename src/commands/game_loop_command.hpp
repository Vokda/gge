#pragma once
#include "command.hpp"
#include <memory>
using namespace std;

class Game_loop_command: public Command
{
	public:
		Game_loop_command(
				std::shared_ptr<GGE_module> m, 
				std::shared_ptr<GGE_module> arg,
				command cmd
				);

		void execute();
		void execute(double d);
	private:
		shared_ptr<Game_loop> _game_loop;
};
