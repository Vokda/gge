#pragma once

#include "command.hpp"

class Graphics;

class Graphics_command: public Command{
	public:
		Graphics_command(
				shared_ptr<GGE_module> graphics, 
				shared_ptr<GGE_module> arg,
				int command);
		void execute();
		enum command {CLEAR_SCREEN, DRAW, RENDER, NR_COMMANDS};
		const string get_command_string() const; 
		bool is_valid_command() const;
	private:
		shared_ptr<Graphics> _graphics;
};
