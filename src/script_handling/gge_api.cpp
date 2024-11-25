#include "gge_api.hpp"
#include <memory>
#include <vector>
#include <iostream>
#include "../sdl_helper.hpp"

#include "../filer.hpp"
#include "../gge_modules/texter.hpp"
#include "../gge_modules/events.hpp"
#include "../gge_modules/graphics.hpp"
#include "../gge_modules/grider.hpp"
#include "../gge_modules/spriter.hpp"
#include "../gge_modules/scroller.hpp"
#include "../gge_modules/agenter.hpp"
#include "../gge_modules/shaper.hpp"
#include "../gge_modules/gui.hpp"

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
    auto gui = static_pointer_cast<gge::GUI>(_core.get_module(GUI));
	return add_module(EVENTS, _gge_init.events(gui));
}

int GGE_API::init_grider(int gt, int w, int h, int ts, int x_offset, int y_offset)
{
	return add_module(GRIDER, _gge_init.grider(gt, w, h, ts, x_offset, y_offset));
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

int GGE_API::init_spriter()
{
	return add_module(SPRITER, _gge_init.spriter(
				static_pointer_cast<Graphics>(_core.get_module(GRAPHICS))));
}

int GGE_API::init_shaper()
{
	return add_module(SHAPER, _gge_init.shaper());
}

int GGE_API::init_agenter()
{
	return add_module(AGENTER, _gge_init.agenter());
}

int GGE_API::init_gui()
{
    auto g = static_pointer_cast<Graphics>(_core.get_module(GRAPHICS));
    auto events =static_pointer_cast<Events>(_core.get_module(EVENTS)); 
    return add_module(GUI, _gge_init.gui(g, events));
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
/*#ifdef DEBUG
	cout << "get_events()"<<endl;
#endif*/
	std::shared_ptr<Events> e = static_pointer_cast<Events>(_core.get_module(EVENTS));
	return e->get_events();
}

int GGE_API::pop_event()
{
#ifdef false //DEBUG
	cout << "get next event (pop_event); ";
	int event = static_pointer_cast<Events>(_core.get_module(EVENTS))->pop_event();
	cout << "event " << event << endl;
	return event;
#else
	return static_pointer_cast<Events>(_core.get_module(EVENTS))->pop_event();
#endif
}

int GGE_API::get_tile_from_mouse(int x, int y)
{
#ifdef false //DEBUG
	if(_x != x and _y != y)
	{
		cout << "DEBUG: raw input [" << x << ", " << y <<"]" << endl;
		_x = x;
		_y = y;
	}
#endif

	auto grid = static_pointer_cast<Grider>(_core.get_module(GRIDER));
	/* TODO only scroll if instantiated
	auto graphics = static_pointer_cast<Graphics>(_core.get_module(GRAPHICS));
	// TODO if top bar add top bar size to y
	y -= graphics->get_viewport(1).h; 
	// test for scroll
	scroll_mouse(x, y);
	y += graphics->get_viewport(1).h; */
	//cube_coord cc = grid->_utils.axial_to_cube(grid->_utils.xy_to_axial(x, y));
#ifdef false //DEBUG
	size_t tile = grid->get_tile(x, y);
	cout << "tile gotten from [" << x << ", " << y << "] => " << tile << endl;
	return tile;
#else
	return grid->get_tile_index(x, y);
#endif
}

void GGE_API::set_tile_color(const vector<int>& c, size_t tile_i)
{
	vector<Uint8> v(c.begin(), c.end());
	SDL_Color color = {v[0], v[1], v[2], 0};
	//SDL_Color color = {c[0], c[1], c[2], c[3]};
#ifdef false //DEBUG
	cout << "setting tile "<< tile_i  <<" color to " << color << endl;
#endif
	shared_ptr<Tile> tile = get_tile(tile_i);
	tile->set_color(color);
#ifdef false //DEBUG
	cout << "setting tile color done" << endl;
#endif
}

const vector<int>& GGE_API::get_neighbors(int tile)
{
	auto grider = static_pointer_cast<Grider>(_core.get_module(GRIDER));
	return grider->get_tile_neighbors_index(tile);
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

void GGE_API::set_tile_custom_data(size_t tile_i, const string& name, void* data)
{
#ifdef DEBUG
	cout << "saving data " << data << " as '" << name << "' to tile " << tile_i << endl;
#endif
	auto tile = get_tile(tile_i);
	(*tile)[name] = data;
}

void* GGE_API::get_tile_custom_data(size_t tile_i, const string& name)
{
#ifdef DEBUG
	cout << "reading data " << name << " from tile " << tile_i << endl;
#endif
	auto tile = get_tile(tile_i);
	return (*tile)[name];
}

size_t GGE_API::load_image(const string& s)
{
	auto graphics = static_pointer_cast<Graphics>(_core.get_module(GRAPHICS));
	Filer& filer = _core.get_filer();
	return graphics->load_image(filer.in_game_dir(s));
}

size_t GGE_API::create_sprite(size_t t, int x, int y)
{
	auto spriter  = static_pointer_cast<Spriter>(_core.get_module(SPRITER));
	SDL_Point p;
	p.x = x;
	p.y = y;
	return spriter->create_sprite(t, p, -1);
}

size_t GGE_API::create_agent(size_t texture, size_t tile)
{
	// get modules
	auto agenter = static_pointer_cast<Agenter>(_core.get_module(AGENTER));
	auto spriter = static_pointer_cast<Spriter>(_core.get_module(SPRITER));

	auto tile_ptr = get_tile(tile);
	const SDL_Point& p = tile_ptr->get_position();
	size_t sprite_i = create_sprite(texture, p.x, p.y);

	auto component =spriter->get_component(sprite_i);
	auto sprite = static_pointer_cast<Sprite>(component);
#ifdef DEBUG
	cout << "Creating agent @ " << p << endl;
	cout << "tile " << tile << endl;
	cout << "spriter " <<spriter << endl;
	cout << "component " <<component<< endl;
	cout << "sprite " << sprite_i << endl;
	cout << "tile_ptr " << tile_ptr << endl;
	cout << "sprite_ptr " << sprite << endl;
#endif
	return agenter->create_agent(tile_ptr, sprite);
}

void GGE_API::move_agent(size_t a, size_t to_tile)
{
	auto agenter = static_pointer_cast<Agenter>(_core.get_module(AGENTER));

#ifdef DEBUG
	cout << "moving agent " << a << " to " << to_tile << endl;
#endif
	agenter->move_agent(a, get_tile(to_tile));
}

void GGE_API::remove_agent(size_t a)
{
	auto agenter = static_pointer_cast<Agenter>(_core.get_module(AGENTER));
	agenter->remove_agent(a);
}

vector<int> GGE_API::get_agents(int i)
{
	vector<int> agents;
	if(i < 0)
	{
		auto agenter = static_pointer_cast<Agenter>(_core.get_module(AGENTER));
		agents = agenter->get_components_indices();
	}
	else
	{
#ifdef DEBUG
		cout << "get agents from tile " << i << endl;
#endif
		auto tile = get_tile(i); 
		auto as = tile->get_agents();
		agents.resize(as.size());
		size_t a_i = 0;
		for(auto a: as)
		{
			agents[a_i++] = a->index;
		}
	}

#ifdef DEBUG
	if(agents.empty())
	{
		cout << "no agents found";
		if(i < 0)
			cout << "found anywhere" << endl;
		else
			cout << "on tile" << i << endl;
	}
	else
	{
		if(i < 0)
		{
			cout << agents.size() << " found in total." << endl;
		}
		else
		{
			cout << agents.size() << " found on tile " << i << endl;
		}
	}
#endif
	return  agents;
}

void GGE_API::change_agent_sprite(int agent, int new_texture)
{
	auto a = get_agent(agent);

	auto sprite = a->sprite;

	auto spriter = static_pointer_cast<Spriter>(_core.get_module(SPRITER));
	spriter->change_texture(sprite, new_texture);
}

// shape

size_t GGE_API::create_shape(int shape_type, int pos_x, int pos_y, int size_x, int size_y, int ms)
{
    auto shaper = static_pointer_cast<Shaper>(_core.get_module(SHAPER));
    SDL_Rect rect{pos_x, pos_y, size_x, size_y};
    return shaper->create_shape(shape_type, rect, ms);
}

// gui

size_t GGE_API::create_button(const string& text)
{
    auto gui = static_pointer_cast<gge::GUI>(_core.get_module(GUI));
    gui->create_button(text);
    return 0;
}
/*
 * PRIVATE FUNCTIONS
 */
shared_ptr<Tile> GGE_API::get_tile(size_t i)
{
	auto grider = static_pointer_cast<Grider>(_core.get_module(GRIDER));
	return grider->get_tile(i);
}

shared_ptr<Agent> GGE_API::get_agent(size_t a)
{
	auto agenter = static_pointer_cast<Agenter>(_core.get_module(AGENTER));
	shared_ptr<Agent> agent = static_pointer_cast<Agent>(agenter->get_component(a));
	return agent;
}
