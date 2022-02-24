#include "core.hpp"
#include <iostream>
#include <chrono>
#include <stdexcept>
#include "graphics.hpp"
#include "events.hpp"
#include "hex/hex_grid.hpp"
#include <functional>
#include <algorithm>
#include "chai_object.hpp"
#include "texter.hpp"
#include "scroller.hpp"
using namespace std;

Core::Core()
{
	_game_loop = nullptr;
	_texter = nullptr;
}


// MODULE INITIALIZERS
void Core::init_graphics(const string&& name, size_t w, size_t h)
{
	_graphics = make_shared<Graphics>(name, w, h, _sdl_helper);
	_scroller = make_shared<Scroller>(
			_graphics->get_screen_width(), 
			_graphics->get_screen_height()
			); // TODO max scroll
	_texter = make_shared<Texter>(_graphics);
}

void Core::init_events()
{
	_events = make_shared<Events>(_sdl_helper);
}

void Core::init_grid(size_t w, size_t h, int size)
{
	_grid = make_shared<Hex_grid>(w, h, size, FLAT_TOP, RECT_ODD_Q); // TODO hard coded for now
}

void Core::init_game_object(Chai_object&& co)
{
	auto fn_names = co.get_fn_names();
	_boxed_value = co.get_boxed_value();

	if(find(fn_names.begin(), fn_names.end(), "game_loop") != fn_names.end())
	{
		_game_loop = std::make_unique<std::function<bool(Boxed_Value&, float)>>(
				co.get_function<bool, float>("game_loop")
				);
	}
}

// MODULE INITIALIZERS END

shared_ptr<Texter> Core::get_texter()
{
	return _texter;
}

void Core::run()
{
	// main loop
	while(not _quit)
	{
		auto start = std::chrono::steady_clock::now();

		_scroller->scroll_grid(_grid);

		_graphics->clear_screen();

		// draw HUD
		_graphics->draw(_texter);
		_texter->tick(); // tick time for temp texts
		// draws everything that isn't HUD
		_graphics->draw(*_grid);


		// game logic
		// game can be quit from inside the game loop by returning true
		_quit = (*_game_loop)(_boxed_value, _delta);

		// actually render shit onto screen
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

void Core::quit()
{
	_quit = true;
}

/*template<typename Events>
std::shared_ptr<Events> Core::get_module()
{
	return _events;
}*/
