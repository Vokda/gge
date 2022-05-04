#pragma once
#include <memory>
#include <map>
#include "registered_gge_modules.hpp"
// gge_begin includes

#include "graphics.hpp"
#include "events.hpp"
#include "hex/hex_grid.hpp"
#include "scroller.hpp"
#include "texter.hpp"
#include "hex/orientation.hpp"
// gge_end includes
class GGE_module;
using namespace std;

class Moduler
{
	public:
		Moduler();

		/*modules_map::iterator find(registered_gge_modules m)
		modules_map::iterator end()*/

		template<typename T>
			shared_ptr<T> get_module();

		// gge_begin functions

		void set_module(const std::string& window_name, size_t width, size_t height, SDL_helper& sh);
		template<>	
			shared_ptr<Graphics> get_module() { return static_pointer_cast<Graphics>(_modules[GRAPHICS]); }

		void set_module(SDL_helper& e);
		template<>	
			shared_ptr<Events> get_module() { return static_pointer_cast<Events>(_modules[EVENTS]); }

		void set_module(size_t w, size_t h, double hex_size, Hex_orientation ho, Coordinate_system cs);
		template<>	
			shared_ptr<Hex_grid> get_module() { return static_pointer_cast<Hex_grid>(_modules[GRID]); }

		void set_module(int w,int h,SDL_Rect* max_scroll);
		template<>	
			shared_ptr<Scroller> get_module() { return static_pointer_cast<Scroller>(_modules[SCROLLER]); }

		void set_module(shared_ptr<Graphics> g);
		template<>	
			shared_ptr<Texter> get_module() { return static_pointer_cast<Texter>(_modules[TEXTER]); }

// gge_end functions

		shared_ptr<GGE_module> operator[](registered_gge_module m); 

		int list_modules() const;

	private:
		typedef map<registered_gge_module, shared_ptr<GGE_module>> modules_map;
		modules_map _modules;

};
