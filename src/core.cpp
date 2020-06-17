#include "core.hpp"
#include "graphics.hpp"
#include "hex/hex_grid.hpp"
#include <cstdarg>
#include <iostream>
using namespace std;

void Core::initialize(Module m, ...)
{
	va_list args;
	va_start(args, m);
	switch(m)
	{
		case GRAPHICS:
			{
				auto s = va_arg(args, const std::string);
				auto w = va_arg(args, size_t);
				auto h = va_arg(args, size_t);
				_graphics = std::shared_ptr<Graphics>(new Graphics(s, w, h));
				break;
			}
		case EVENT_HANDLER:
			_events = std::shared_ptr<Events>(new Events());
			break;
		case GRID:
			{
				auto w = va_arg(args, size_t);
				auto h = va_arg(args, size_t);
				auto size = va_arg(args, int);
				_grid = std::shared_ptr<Hex_grid>(new Hex_grid(w, h, size, Hex_grid::FLAT_TOP));
				break;
			}
		default:
			throw "Not implemented yet!";
			break;
	}
	va_end(args);
}

bool Core::handle_events()
{
	auto event = _events->get_event();
	if(event == Events::events::QUIT)
		return true;
	else
		return false;
}

void Core::render(bool cls)
{
	if(cls)
		_graphics->clear_screen();

	game_loop();
	_graphics->draw_grid(*_grid);

	_graphics->render();
}

void Core::check_modules_initiated()
{
	if(not _graphics)
		cout << "Warning: Graphics not initiated!" << endl;
	if(not _events)
		cout << "Warning: Events not initiated!" << endl;
}

void Core::game_loop()
{}
