#include "core.hpp"
#include <iostream>
#include <chrono>
#include <stdexcept>
#include "graphics.hpp"
#include "events.hpp"
#include "hex/hex_grid.hpp"
#include <functional>
using namespace std;

bool Core::handle_events()
{
	auto event = _events->get_event();
	if(event == Events::events::QUIT)
		return true;
	else
		return false;
}


// MODULE INITIALIZERS
void Core::init_graphics(const string&& name, size_t w, size_t h)
{
	_graphics = make_shared<Graphics>(name, w, h, _sdl_helper);
}

void Core::init_events()
{
	_events = make_shared<Events>(_sdl_helper);
}

void Core::init_grid(size_t w, size_t h, int size)
{
	_grid = make_shared<Hex_grid>(w, h, size, Hex_grid::FLAT_TOP);
}

void Core::init_game_loop(const std::function<bool(float)>& f)
{
	_game_loop = std::make_shared<std::function<bool(float)>>(f);
}
// MODULE INITIALIZERS END

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
