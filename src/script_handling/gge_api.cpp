#include "gge_api.hpp"
#include <memory>
#include <vector>
#ifdef DEBUG
#include <iostream>
#endif
using namespace std;

GGE_API::GGE_API(Core& core):
	_core(core)
{}

const string GGE_API::hello()
{
	return "GGE API says hello!";
}

size_t GGE_API::create_text(const string& text, int view_port)
{
	return create_text(text, view_port);
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
	auto texter = _core.get_module<Texter>();
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
	auto texter = _core.get_module<Texter>();
	return texter->modify_text(i, v);
}

std::vector<int> GGE_API::get_mouse_position()
{
	std::shared_ptr<Events> e = _core.get_module<Events>();
	vector<int> p = e->get_mouse_position();
	//p[1] += _core.get_module<Graphics>()->get_viewport(1).h; // TODO make this better
	return p;
}


const std::vector<int>& GGE_API::get_events() const
{
	return _core.get_module<Events>()->get_events();
}

int GGE_API::get_hex_from_mouse(int x, int y)
{
#ifdef DEBUG
	cout << "DEBUG: raw input [" << x << ", " << y <<"]" << endl;
#endif

	shared_ptr<Hex_grid> grid = _core.get_module<Hex_grid>();
	// TODO if top bar add top bar size to y
	y -= _core.get_module<Graphics>()->get_viewport(1).h; 
	// test for scroll
	scroll_mouse(x, y);
	y += _core.get_module<Graphics>()->get_viewport(1).h; 
	cube_coord cc = grid->_utils.axial_to_cube(grid->_utils.xy_to_axial(x, y));
	int i = grid->get_hex_index(cc);

	return i;
}

void GGE_API::set_hex_color(const vector<int>& c, size_t hex_i)
{
	vector<Uint8> v(c.begin(), c.end());
	SDL_Color color = {v[0], v[1], v[2], v[3]};
	shared_ptr<Hex_grid> grid = _core.get_module<Hex_grid>();
	Hex& hex = grid->get_hex(hex_i);
	hex.set_color(color);
}

bool GGE_API::scroll(vector<int>& mouse_pos)
{
	auto scroller = _core.get_module<Scroller>();
	SDL_Point p;
	p.x = mouse_pos[0];
	p.y = mouse_pos[1];
	return scroller->scroll(p);
}

void GGE_API::scroll_mouse(int& x, int& y)
{
	auto scroller = _core.get_module<Scroller>();
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

void GGE_API::add_command(const string& cmd)
{
	return _core.add_command(cmd);
}
