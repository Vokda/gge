#pragma once
#include "../graphics.hpp"
#include "command.hpp"

class Graphics_command: public Command
{
	public:
		void draw(shared_ptr<Texter> texter);
		void draw(const Shape& shape);
		void clear_screen();
		void render();
		void draw(const Hex_grid& grid);
		 Graphics_command(
				std::shared_ptr<GGE_module> m, 
				rgm type,
				std::shared_ptr<GGE_module> arg,
				rgm arg_type,
				command cmd
				);

};

