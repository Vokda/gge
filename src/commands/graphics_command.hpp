#pragma once
#include "../graphics.hpp"
#include "command.hpp"
class Hex_grid;

class Graphics_command: public Command
{
	public:
		Graphics_command(
				std::shared_ptr<GGE_module> m, 
				rgm type,
				std::shared_ptr<GGE_module> arg,
				rgm arg_type,
				command cmd);
		void render();
		void clear_screen();
		void draw(const Hex_grid& grid);
		void draw(shared_ptr<Texter> texter);
		void draw(const Shape& shape);

};

