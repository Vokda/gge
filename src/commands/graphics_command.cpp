#include "graphics_command.hpp"
#include "../graphics.hpp"
#include "../hex/hex_grid.hpp"
#include <memory>

Graphics_command::Graphics_command(
				std::shared_ptr<GGE_module> m, 
				rgm type,
				std::shared_ptr<GGE_module> arg,
				rgm arg_type,
				command cmd): Command(m, type, arg, arg_type, cmd)
{
	
}

void Graphics_command::clear_screen()
{
	static_pointer_cast<Graphics>(_module)->clear_screen();
}

void Graphics_command::draw(shared_ptr<Texter> texter)
{
	static_pointer_cast<Graphics>(_module)->draw(texter);
}

void Graphics_command::draw(const Hex_grid& Grid)
{
	static_pointer_cast<Graphics>(_module)->draw(Grid);
}

void Graphics_command::render()
{
	static_pointer_cast<Graphics>(_module)->render();
}

void Graphics_command::draw(const Shape& shape)
{
	static_pointer_cast<Graphics>(_module)->draw(shape);
}


