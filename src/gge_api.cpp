#include "gge_api.hpp"
#include "core.hpp"
#include "events.hpp"
#include <memory>
#include "texter.hpp"
#include <vector>
#include "hex/utils.hpp"
#include "hex/hex_grid.hpp"
using namespace std;

GGE_API::GGE_API(Core& core):
	_core(core)
{}

const string GGE_API::hello()
{
	return "GGE API says hello!";
}

size_t GGE_API::create_text(const string& text, int x, int y)
{
	auto texter = _core.get_texter();
	return texter->create_text(text, {x, y});
}

size_t GGE_API::create_text(
		const string& text, 
		vector<int> color,
		vector<int> size,
		int milliseconds
		)
{
	auto texter = _core.get_texter();
	vector<Uint8> casted_v(color.begin(), color.end());
	SDL_Color c = {casted_v[0], casted_v[1], casted_v[2], casted_v[3]};

	// position
	SDL_Rect s = {size[0], size[1], size[2], size[3]};

	return texter->create_text(
			text, 
			c,
			s,
			milliseconds
			);
}

std::vector<int> GGE_API::get_mouse_position()
{
	std::shared_ptr<Events> e = _core.get_module<Events>();
	return e->get_mouse_position();
}


const std::vector<int>& GGE_API::get_events() const
{
	return _core.get_module<Events>()->get_events();
}

int GGE_API::get_hex_from_mouse(int x, int y)
{
	shared_ptr<Hex_grid> grid = _core.get_grid();
	cube_coord cc = grid->_utils.axial_to_cube(grid->_utils.xy_to_axial(x, y));
	return grid->get_hex_index(cc);
}
