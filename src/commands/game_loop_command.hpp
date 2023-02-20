#pragma once
#include "command.hpp"
#include <memory>
#include "../gge_modules/game_loop.hpp"
using namespace std;


class Game_loop_command: public Command
{
	public:
		Game_loop_command(
				std::shared_ptr<Game_loop> m, 
				std::shared_ptr<GGE_module> a, 
				double& arg
				);

		void execute();
		const string get_command_string() const;
	private:
		shared_ptr<Game_loop> _game_loop;
		double& _arg;
};
