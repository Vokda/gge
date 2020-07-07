#include "core.hpp"
#include "graphics.hpp"
#include "events.hpp"
#include "hex/hex_grid.hpp"
#include <cstdarg>
#include <iostream>
#include <functional>
#include <chrono>
#include <stdexcept>
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
		case GAME_LOOP:
			{
				auto f = va_arg(args, const std::function<bool(float)>);
				_game_loop = std::make_shared<std::function<bool(float)>>(f);
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

void Core::run()
{
	// main loop
	while(not _quit)
	{
		auto start = std::chrono::steady_clock::now();

		_quit = handle_events();
		_graphics->clear_screen();

		// draws everything that isn't HUD
		_graphics->draw_grid(*_grid);

		// game logic
		// game can be quit from inside the game loop by returning true
		_quit = (*_game_loop)(_delta);
		_graphics->render();

		auto end = std::chrono::steady_clock::now();

		// calculate delta
		std::chrono::duration<double> elapsed_seconds = end - start;
		_delta = elapsed_seconds.count();
	}
}

void Core::check_modules_initiated()
{
	if(not _graphics)
		cerr << "Warning: Graphics not initiated!" << endl;
	if(not _events)
		cerr << "Warning: Events not initiated!" << endl;
	if(not _grid)
		cerr << "Warning: Grid not initiated!" << endl;
	if(not _game_loop)
	{
		std::domain_error de("No game loop provided!");
		throw de; 
	}
}
