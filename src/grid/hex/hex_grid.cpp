#include "hex_grid.hpp"
#include "hex.hpp"
#include <iostream>
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

Hex_grid::Hex_grid(size_t width, size_t height, double size, GGE::Hex_orientation ho, GGE::Coordinate_system cs, int x_offset, int y_offset):
	Grid(),
	_layout(GGE::Orientation(ho, size), cs), 
	_x_offset(x_offset),
	_y_offset(y_offset),
	_utils(_layout)
{
	// in case of square grid
	bool success = true;
	cout << "Grid -";

	if(width <= 0 or height <= 0)
		throw runtime_error("width and height of grid needs to be > 0!");

	if(width >= INT_MAX / height)
	{
		throw runtime_error("width x height TOO BIG for system to handle!");
	}

	// && success is for breaking out of outer loop
	for(size_t w = 0; w < height && success; ++w)
	{
		for(size_t h = 0; h < width; ++h)
		{
			try
			{
				cube_coord cc = _utils.offset_coord_to_cube(h, w);
				SDL_Point center_point = _utils.calc_center_point(h, w);
				center_point.x += x_offset;
				center_point.y += y_offset;
				shared_ptr<Hex> hex = make_shared<Hex>(cc, center_point, size, _utils);
				_grid.push_back(hex);
				int i = _grid.size() - 1;
#ifdef DEBUG
				cout << "Made hex ["<< i << "] at " << *hex << endl;
				map_cube_to_i(hex->get_cube_coords(), i);
#endif
			}
			catch(char const* e)
			{
				success = false;
				cerr << "Could not create grid: " << e << endl;
				break;
			}
		}
	}

	// set neighbors
	for(auto tile: _grid)
	{
		shared_ptr<Hex> hex = static_pointer_cast<Hex>(tile);
		hex->set_neighbors(
				get_neighbors(
					hex->get_cube_coords()));
	}

	if(success)
		cout << "OK" << endl;
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
	try
	{
#ifdef false //DEBUG TODO should have some better way of doing it 
		int hash_cube_coordinate = hash_cube_coord( cc.q, cc.r, cc.s );
		cout << "hash cube coord " << hash_cube_coordinate << endl;
		size_t index = _cube_coords_to_i_map.at(hash_cube_coordinate);
		cout << "tile index " << index << endl;
		return index;
#else
		return _cube_coords_to_i_map.at(hash_cube_coord( cc.q, cc.r, cc.s ) );
#endif
	}
	catch(const out_of_range& oor)
	{
		return -1;
	}
}

int Hex_grid::get_tile(int x, int y)
{
	x -= _x_offset;
	y -= _y_offset;
	return get_hex_index(
			_utils.axial_to_cube(
				_utils.xy_to_axial(x, y)));
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
#ifdef DEBUG
	// TODO Oh god, why are there two functions with the same name in the parent??
	cout << "number of neighbors of hex " << Grid::get_tile(get_hex_index(cc)) << ": ";
#endif
	for(auto& rel_n: _utils.get_relative_neighbors())
	{
		cube_coord neighbor = cc + rel_n;
		shared_ptr<Tile> i = get_hex(neighbor);
		if(i) // TODO no need to recalculate every time. Cache it!
		{
			neighbors.push_back(i);
		}
	}
#ifdef DEBUG
	cout << neighbors.size() << endl;
#endif
	return neighbors;
}

vector<int> Hex_grid::get_neighbors_index(cube_coord cc)
{
	vector<int> neighbors; // at most 6 neighbors
#ifdef DEBUG
	// TODO Oh god, why are there two functions with the same name in the parent??
	cout << "number of neighbors of hex " << Grid::get_tile(get_hex_index(cc)) << ": ";
#endif
	for(auto& rel_n: _utils.get_relative_neighbors())
	{
		cube_coord neighbor = cc + rel_n;
		int i = get_hex_index(neighbor);
		if(i > -1) // TODO no need to recalculate every time. Cache it!
		{
			neighbors.push_back(i);
		}
	}
#ifdef DEBUG
	cout << neighbors.size() << endl;
#endif
	return neighbors;
}
