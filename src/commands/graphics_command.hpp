#pragma once
#include "../graphics.hpp"
#include "command.hpp"

class graphics_command: Command
{
	public:
		void draw(const Shape& shape);
		void draw(const Hex_grid& grid);
		void render();
		void draw(shared_ptr<Texter> texter);
		void clear_screen();

};

