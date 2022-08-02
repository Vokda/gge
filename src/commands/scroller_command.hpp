#pragma once
#include "../scroller.hpp"
#include "command.hpp"

class Scroller_command: public Command
{
	public:
		 Scroller_command(
				std::shared_ptr<GGE_module> m, 
				rgm type,
				std::shared_ptr<GGE_module> arg,
				rgm arg_type,
				command cmd
				);
		void scroll_grid(shared_ptr<Hex_grid> grid);

};

