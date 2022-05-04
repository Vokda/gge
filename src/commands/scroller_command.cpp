#include "scroller_command.hpp"
#include "../scroller.hpp"

void scroller_command::scroll_grid(shared_ptr<Hex_grid> grid)
{
	static_pointer_cast<Scroller>(_module)->scroll_grid(grid);
}


