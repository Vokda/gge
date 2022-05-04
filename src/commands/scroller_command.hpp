#pragma once
#include "../scroller.hpp"
#include "command.hpp"

class scroller_command: Command
{
	public:
		void scroll_grid(shared_ptr<Hex_grid> grid);

};

