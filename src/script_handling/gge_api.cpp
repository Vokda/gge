#include "gge_api.hpp"
#include <memory>
#include <vector>
#include <iostream>

#include "../texter.hpp"
#include "../events.hpp"
#include "../graphics.hpp"
#include "../hex/hex_grid.hpp"
#include "../scroller.hpp"

using namespace std;

GGE_API::GGE_API(Core& core):
	_core(core)
{
	add_module(NONE, _gge_init.none());
}

void GGE_API::hello()
{
	cout << "GGE API says hello!\n" << endl;
}

// init 
int GGE_API::init_graphics(const string& s, size_t w, size_t h)
{
	return add_module(GRAPHICS, _gge_init.graphics(s, w, h));
}

int GGE_API::init_events()
{
	return add_module(EVENTS, _gge_init.events());
}

int GGE_API::init_grid(size_t w, size_t h, int s)
{
	return add_module(GRID, _gge_init.grid(w, h, s));
}

int GGE_API::init_game_loop()
{
	return add_module(GAME_LOOP, _gge_init.game_loop(*_script_engine, _core));
}

int GGE_API::init_texter()
{
	return add_module(TEXTER, _gge_init.texter(
				static_pointer_cast<Graphics>(_core.get_module(GRAPHICS))
				));
}

// init end



size_t GGE_API::create_text(const string& text, int view_port)
{
	return create_text(
			text, 
			{255,255,255,255},
			{0,0,100,100},
			1000,
			view_port);
}

size_t GGE_API::create_text(const string& text, int view_port, int ms = 1000, int x = -1, int y = -1)
{
	return create_text(text, {255,255,255,255}, {0,0,0,0}, ms, view_port);
}

size_t GGE_API::create_text(
		const string& text, 
		vector<int> color,
		vector<int> size,
		int milliseconds,
		int view_port
		)
{
	auto texter = static_pointer_cast<Texter>(_core.get_module(TEXTER));
	vector<Uint8> casted_v(color.begin(), color.end());
	SDL_Color c = {casted_v[0], casted_v[1], casted_v[2], casted_v[3]};

	// position
	SDL_Rect s = {size[0], size[1], size[2], size[3]};

	return texter->create_text(
			text, 
			c,
			s,
			milliseconds,
			view_port
			);
}

bool GGE_API::modify_text(size_t i, int v)
{
	auto texter = static_pointer_cast<Texter>(_core.get_module(TEXTER));
	return texter->modify_text(i, v);
}

/*
 * EVENTS
 */

std::vector<int> GGE_API::get_mouse_position()
{
	std::shared_ptr<Events> e = static_pointer_cast<Events>(_core.get_module(EVENTS));
	vector<int> p = e->get_mouse_position();
	//p[1] += _core.get_module<Graphics>()->get_viewport(1).h; // TODO make this better
	return p;
}


const std::queue<int>& GGE_API::get_events() const
{
	std::shared_ptr<Events> e = static_pointer_cast<Events>(_core.get_module(EVENTS));
	return e->get_events();
}

int GGE_API::pop_event()
{
	return static_pointer_cast<Events>(_core.get_module(EVENTS))->pop_event();
}

int GGE_API::get_hex_from_mouse(int x, int y)
{
#ifdef DEBUG
	if(_x != x and _y != y)
	{
		cout << "DEBUG: raw input [" << x << ", " << y <<"]" << endl;
		_x = x;
		_y = y;
	}
#endif

	auto grid = static_pointer_cast<Hex_grid>(_core.get_module(GRID));
	/* TODO only scroll if instantiated
	auto graphics = static_pointer_cast<Graphics>(_core.get_module(GRAPHICS));
	// TODO if top bar add top bar size to y
	y -= graphics->get_viewport(1).h; 
	// test for scroll
	scroll_mouse(x, y);
	y += graphics->get_viewport(1).h; */
	cube_coord cc = grid->_utils.axial_to_cube(grid->_utils.xy_to_axial(x, y));
	int i = grid->get_hex_index(cc);

	return i;
}

void GGE_API::set_hex_color(const vector<int>& c, size_t hex_i)
{
	vector<Uint8> v(c.begin(), c.end());
	SDL_Color color = {v[0], v[1], v[2], v[3]};
	Hex& hex = get_hex(hex_i);
	hex.set_color(color);
}

bool GGE_API::scroll(vector<int>& mouse_pos)
{
	auto scroller = static_pointer_cast<Scroller>(_core.get_module(SCROLLER));
	SDL_Point p;
	p.x = mouse_pos[0];
	p.y = mouse_pos[1];
	return scroller->scroll(p);
}

void GGE_API::scroll_mouse(int& x, int& y)
{
	auto scroller = static_pointer_cast<Scroller>(_core.get_module(SCROLLER));
	SDL_Point scrolled = scroller->get_scrolled();
	x -= scrolled.x;
	y -= scrolled.y;
#ifdef DEBUG
	cout << "DEBUG: " << scrolled << endl;
	cout << "DEBUG: processed input [" << x << ", " << y <<"]" << endl;
#endif
}

void GGE_API::create_shape(int shape, const vector<int>& p)
{
	// TODO
	cout <<"shape!" << endl;
}

void GGE_API::add_command(rgm module, int command, rgm arg)
{
	_core.add_command(module, command, arg);
}

int GGE_API::add_module(rgm m, shared_ptr<GGE_module> ptr)
{
	_core.add_module(m, ptr);
	return m;
}

void GGE_API::quit()
{
	_core.quit();
}

void GGE_API::set_hex_custom_data(size_t hex_i, const string& name, void* data)
{
#ifdef DEBUG
	cout << "saving data " << data << " as " << name << " to hex " << hex_i << endl;
#endif
	auto& hex = get_hex(hex_i);
	hex[name] = data;
}

void* GGE_API::get_hex_custom_data(size_t hex_i, const string& name)
{
#ifdef DEBUG
	cout << "reading data " << name << " from hex " << hex_i << endl;
#endif
	auto hex = get_hex(hex_i);
	return hex[name];
}

/*
void GGE_API::set_hex_data_number(const string& name, double d, size_t i)
{
	Hex& hex = get_hex(i);
	//hex.set_custom_data(name, new(sizeof(d)));
}

void* GGE_API::get_hex_data_number(const string& name, size_t i)
{
	Hex& hex = get_hex(i);
	//return hex.get_custom_data(name);
}


void GGE_API::set_hex_data_text(const string& name, const string& text, size_t i)
{
	Hex& hex = get_hex(i);
	//hex.set_custom_data(name, new(sizeof(text));
}

void GGE_API::get_hex_data_text(const string& name, size_t i)
{
	Hex& hex = get_hex(i);
	//hex.get_custom_data(name));
}
*/



/*
 * PRIVATE FUNCTIONS
 */
Hex& GGE_API::get_hex(size_t i)
{
	auto grid = static_pointer_cast<Hex_grid>(_core.get_module(GRID));
	return grid->get_hex(i);
}
