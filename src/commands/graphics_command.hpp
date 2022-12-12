#pragma once

#include "../graphics.hpp"
#include "command.hpp"

class Graphics_command: public Command{
	public:
		Graphics_command(
				shared_ptr<GGE_module> graphics, 
				int command,
				shared_ptr<GGE_module> arg=nullptr);
		void execute();
		enum command {CLEAR_SCREEN, DRAW, RENDER};
		const string get_command_string() const; 
	private:
		shared_ptr<Graphics> _graphics;
};
