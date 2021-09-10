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
using namespace std;

Core::Core()
{
	_game_loop = nullptr;
	_event_handle = nullptr;
	_texter = nullptr;
}


// MODULE INITIALIZERS
void Core::init_graphics(const string&& name, size_t w, size_t h)
{
	_graphics = make_shared<Graphics>(name, w, h, _sdl_helper);
	_texter = make_shared<Texter>(_graphics->get_renderer());
}

void Core::init_events()
{
	_events = make_shared<Events>(_sdl_helper);
}

void Core::init_grid(size_t w, size_t h, int size)
{
	_grid = make_shared<Hex_grid>(w, h, size, Hex_grid::FLAT_TOP);
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

	if(find(fn_names.begin(), fn_names.end(), "event_handle") != fn_names.end())
	{
		_event_handle = make_shared<std::function<void(Boxed_Value&, vector<int>)>>(
				co.get_function<void, vector<int>>("event_handle")
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

		handle_events();
		_graphics->clear_screen();


		// draws everything that isn't HUD
		_graphics->draw_grid(*_grid);

		// HUD
		_texter->tick();

		// game logic
		// game can be quit from inside the game loop by returning true
		_quit = (*_game_loop)(_boxed_value, _delta);


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
	if(not _event_handle)
	{
		std::domain_error de("No event handle function provided!");
		throw de; 
	}
}

void Core::handle_events()
{
	(*_event_handle)(_boxed_value, _events->get_events());
}

void Core::quit()
{
	_quit = true;
}

template<typename Events>
std::shared_ptr<Events> Core::get_module()
{
	return _events;
}
