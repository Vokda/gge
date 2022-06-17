#include "graphics_command.hpp"
#include "../graphics.hpp"

void graphics_command::draw(const Shape& shape)
{
	static_pointer_cast<Graphics>(_module)->draw(shape);
}

void graphics_command::draw(const Hex_grid& grid)
{
	static_pointer_cast<Graphics>(_module)->draw(grid);
}

void graphics_command::render()
{
	static_pointer_cast<Graphics>(_module)->render();
}

void graphics_command::draw(shared_ptr<Texter> texter)
{
	static_pointer_cast<Graphics>(_module)->draw(texter);
}

void graphics_command::clear_screen()
{
	static_pointer_cast<Graphics>(_module)->clear_screen();
}


