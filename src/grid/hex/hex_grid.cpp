#include "hex_grid.hpp"
#include "hex.hpp"
#include <iostream>
#include "hex_utils.hpp"
#include <stdexcept>
#include "coords.hpp"
using namespace std;


/*Hex_grid::Hex_grid(const Hex_grid& hg):
	_hex_size(hg._hex_size),
	_layout(hg._layout),
	_utils(hg._layout)
{
}*/

Hex_grid::Hex_grid(size_t width, size_t height, double size, Hex_orientation ho, Coordinate_system cs):
	_layout(Orientation(ho, size), cs), 
	Grid(),
	_utils(_layout)
{
	size_t k = 1;

	// in case of square grid
	bool success = true;
	cout << "Grid -";
	// && success is for breaking out of outer loop
	for(size_t w = 0; w < height && success; ++w)
	{
		for(size_t h = 0; h < width; ++h)
		{
			try
			{
				cube_coord cc = _utils.offset_coord_to_cube(h, w);
				SDL_Point center_point = _utils.calc_center_point(cc);
				shared_ptr<Hex> hex = make_shared<Hex>(cc, center_point, size, _utils);
				_grid.push_back(hex);
				int i = _grid.size() - 1;
#ifdef DEBUG
				cout << "Made hex ["<< i << "] at " << hex;
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
	if(success)
		cout << "OK" << endl;
}

/*Hex Hex_grid::hex_add(const Hex& a, const Hex& b)
{
	auto c_a = a.get_cube_coordinate();
	auto c_b = b.get_cube_coordinate();
	return Hex(c_a.q + c_b.q, c_a.r + c_b.r, c_a.s + c_b.s, _hex_size);
}*/

/*Hex& Hex_grid::get_hex(int q, int r, int s)
{
	return get_hex(_cube_coords_to_i_map[hash_cube_coord(q,r,s)]);
}*/

size_t Hex_grid::get_hex_index(cube_coord cc)
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

size_t Hex_grid::get_tile(int x, int y)
{
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
