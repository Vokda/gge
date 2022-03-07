#include "core.hpp"
#include <iostream>
#include <chrono>
#include <stdexcept>
/*#include "graphics.hpp"
#include "events.hpp"
#include "hex/hex_grid.hpp"*/
#include <functional>
#include <algorithm>
#include "chai_object.hpp"
/*#include "texter.hpp"
#include "scroller.hpp"*/
#include "registered_gge_modules.hpp"
class Initializer;
using namespace std;

Core::Core()
{
	_graphics = _moduler.get_module<Graphics>();
	_scroller = _moduler.get_module<Scroller>();
	_grid = _moduler.get_module<Hex_grid>();
	_game_loop = nullptr;
}

void Core::init_game_object(Chai_object& co)
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

void Core::run()
{
	// main loop
	/* TODO
	 * redo the main loop so that it can offer more 
	 * flexibility with which modules are used and in what order
	 */
	while(not _quit)
	{
		auto start = std::chrono::steady_clock::now();

		_scroller->scroll_grid(_grid);

		_graphics->clear_screen();

		// draw HUD
		//_graphics->draw(_texter);
		//_texter->tick(); // tick time for temp texts
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
	vector<registered_gge_module> important = {GRAPHICS, EVENTS, GRID};
	for(auto m: important)
	{
		if(_moduler[m] == nullptr)
		{
			cerr << "Warning: " << GGE_module::get_module_name(m) <<  " not initiated!" << endl;
		}
	}
	/*if(not _graphics)
		cerr << "Warning: Graphics not initiated!" << endl;
	if(not _events)
		cerr << "Warning: Events not initiated!" << endl;
	if(not _grid)
		cerr << "Warning: Grid not initiated!" << endl;*/

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
