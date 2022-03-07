#include "moduler.hpp"
#include "gge_module.hpp"
// gge_begin includes
#include "graphics.hpp"
#include "events.hpp"
#include "hex/hex_grid.hpp"
#include "scroller.hpp"
#include "texter.hpp"
#include <iostream>
using namespace std;
Moduler::Moduler()
{
}

/*modules_map::iterator Moduler::find(registered_gge_module m)
{
	return _modules.find(m);
}

modules_map::iterator Moduler::end()
{
	return _modules.end();
}*/

shared_ptr<GGE_module> Moduler::operator[](registered_gge_module m) 
{ 
	return _modules[m];
}


// gge_begin fn_defs

void Moduler::set_module(const std::string& window_name, size_t width, size_t height, SDL_helper& sh)
{ 
	cout << "Module Graphics initialization..." << endl;
	_modules[GRAPHICS] = make_shared<Graphics>(window_name, width, height, sh); 
	cout << "Module Graphics initialization complete!" << endl;
}

void Moduler::set_module(SDL_helper& e)
{ 
	cout << "Module Events initialization..." << endl;
	_modules[EVENTS] = make_shared<Events>(e); 
	cout << "Module Events initialization complete!" << endl;
}

void Moduler::set_module(size_t w, size_t h, double hex_size, Hex_orientation ho, Coordinate_system cs)
{ 
	cout << "Module Hex_grid initialization..." << endl;
	_modules[GRID] = make_shared<Hex_grid>(w, h, hex_size, ho, cs); 
	cout << "Module Hex_grid initialization complete!" << endl;
}

void Moduler::set_module(int w,int h,SDL_Rect* max_scroll)
{ 
	cout << "Module Scroller initialization..." << endl;
	_modules[SCROLLER] = make_shared<Scroller>(w, h, max_scroll); 
	cout << "Module Scroller initialization complete!" << endl;
}

void Moduler::set_module(shared_ptr<Graphics> g)
{ 
	cout << "Module Texter initialization..." << endl;
	_modules[TEXTER] = make_shared<Texter>(g); 
	cout << "Module Texter initialization complete!" << endl;
}

// gge_end fn_defs
