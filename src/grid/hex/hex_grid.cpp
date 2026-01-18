#include "hex_grid.hpp"
#include "hex.hpp"
#include "hex_utils.hpp"
#include <stdexcept>
#include "coords.hpp"
#include <climits>
using namespace std;


/*Hex_grid::Hex_grid(const Hex_grid& hg):
	_hex_size(hg._hex_size),
	_layout(hg._layout),
	_utils(hg._layout)
{
}*/

Hex_grid::Hex_grid(int width, int height, double size, GGE::Hex_orientation ho, GGE::Coordinate_system cs, int x_offset, int y_offset):
	Grid(width, height),
	_layout(GGE::Orientation(ho, size), cs), 
	_x_offset(x_offset),
	_y_offset(y_offset),
	_utils(_layout)
{
	if(width <= 0 or height <= 0)
		throw runtime_error("width and height of grid needs to be > 0!");

	if(width >= INT_MAX / height)
	{
		throw runtime_error("width x height TOO BIG for system to handle!");
	}

	create_grid(width, height, size, x_offset, y_offset);

	set_tile_neighbors();
}

void Hex_grid::set_tile_neighbors()
{
	// set neighbors
	for(auto tile: _grid)
	{
		shared_ptr<Hex> hex = static_pointer_cast<Hex>(tile);
		hex->set_neighbors(
				get_neighbors(
					hex->get_cube_coords()));
	}
}

void Hex_grid::create_grid(int width, int height, double tile_size, int x_offset, int y_offset)
{
	for(int w = 0; w < height; ++w)
	{
		for(int h = 0; h < width; ++h)
		{
			cube_coord cc = _utils.offset_coord_to_cube(h, w);
			SDL_Point center_point = _utils.calc_center_point(h, w);
			center_point.x += x_offset;
			center_point.y += y_offset;
			shared_ptr<Hex> hex = std::make_shared<Hex>(cc, center_point, tile_size, _utils);
			_grid.push_back(hex);
			int i = _grid.size() - 1;
			map_cube_to_i(cc, i);
			_log_stream << "Made hex [" << i << "] at " << *hex;
		}
	}
	_log_stream.flush();
}

/*Hex Hex_grid::hex_add(const Hex& a, const Hex& b)
{
	auto c_a = a.get_cube_coordinate();
	auto c_b = b.get_cube_coordinate();
	return Hex(c_a.q + c_b.q, c_a.r + c_b.r, c_a.s + c_b.s, _hex_size);
}*/

shared_ptr<Hex> Hex_grid::get_hex(cube_coord cc)
{
	try
	{
		int index = _cube_coords_to_i_map.at(hash_cube_coord( cc.q, cc.r, cc.s ) );
		return static_pointer_cast<Hex>(_grid[index]);
	}
	catch(const out_of_range& oor)
	{
		return nullptr;
	}
}

int Hex_grid::get_hex_index(cube_coord cc)
{
	int hash = hash_cube_coord(cc.q, cc.r, cc.s);
	//_log.debug("Getting hex index for cube coord %i,%i,%i (hash %i)", cc.q, cc.r, cc.s, hash);
	try {
		return _cube_coords_to_i_map.at(hash);
	} catch(const out_of_range& oor) {
		//_log.debug("No hex found");
		return -1;
	}
}

int Hex_grid::get_tile(int x, int y)
{
	x -= _x_offset;
	y -= _y_offset;
	//_log.debug("Getting hex at mouse position %i,%i", x, y);
	axial_coord ac = _utils.xy_to_axial(x, y);
	//_log.debug("Converted to axial coord %f,%f", ac.q, ac.r);
	cube_coord cc = _utils.axial_to_cube(ac);
	//_log.debug("Converted to cube coord %f,%f,%f", cc.q, cc.r, cc.s);
	int index = get_hex_index(cc);
	//_log.debug("Hex index at mouse position %i,%i is %i", x + _x_offset, y + _y_offset, index);
	return index;
}

// PRIVATE MEMBERS
void Hex_grid::map_cube_to_i(cube_coord cc, size_t i)
{
	_cube_coords_to_i_map[hash_cube_coord(cc.q, cc.r, cc.s)] = i;
}

int Hex_grid::hash_cube_coord(int q, int r, int s)
{
	unsigned long hash = 5381;
	hash = ((hash << 5) + hash) + (q);
	hash = ((hash << 5) + hash) + (r);
	hash = ((hash << 5) + hash) + (s);
	return hash;
}


vector<shared_ptr<Tile>> Hex_grid::get_neighbors(cube_coord cc)
{
	vector<shared_ptr<Tile>> neighbors; // at most 6 neighbors
	stringstream ss;
	//ss << "number of neighbors of hex " << *get_hex(cc) << ": "; // TODO borked?
	for(auto& rel_n: _utils.get_relative_neighbors())
	{
		cube_coord neighbor = cc + rel_n;
		shared_ptr<Tile> i = get_hex(neighbor);
		if(i) // TODO no need to recalculate every time. Cache it!
		{
			neighbors.push_back(i);
		}
	}
	ss << neighbors.size() << endl;
	_log_stream << ss.str();
	_log_stream.flush();
	return neighbors;
}

vector<int> Hex_grid::get_neighbors_index(cube_coord cc)
{
	vector<int> neighbors; // at most 6 neighbors
	_log_stream << "Getting neighbors for hex at " << cc.q << "," << cc.r << "," << cc.s;
	for(auto& rel_n: _utils.get_relative_neighbors())
	{
		cube_coord neighbor = cc + rel_n;
		int i = get_hex_index(neighbor);
		if(i > -1) // TODO no need to recalculate every time. Cache it!
		{
			neighbors.push_back(i);
		}
	}
	_log_stream << "Relative nr of neighbors: " << neighbors.size();
	return neighbors;
}
