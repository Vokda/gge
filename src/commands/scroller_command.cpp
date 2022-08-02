#include "scroller_command.hpp"
#include "../scroller.hpp"

void Scroller_command::scroll_grid(shared_ptr<Hex_grid> grid)
{
	static_pointer_cast<Scroller>(_module)->scroll_grid(grid);
}

 Scroller_command::Scroller_command(
				std::shared_ptr<GGE_module> m, 
				rgm type,
				std::shared_ptr<GGE_module> arg,
				rgm arg_type,
				command cmd
				): Command(m, type, arg, arg_type, cmd)
{
	
}


