#include "hex_grid.hpp"
#include "hex.hpp"
#include <iostream>
#include "utils.hpp"
using namespace std;

Hex_grid::Hex_grid(size_t width, size_t height, int size, Hex_orientation ho):
	_hex_size(size), 
	_layout(set_orientation(ho), size, {0, 0}),
	_utils(_layout)
{
	// flat toped hex
	int hex_width = _hex_size * 2;
	int hex_height = _hex_size * sqrt(3);


	size_t k = 1;
	// in case of square grid
	bool success = true;
	cout << "Grid -";
	// && success is for breaking out of outer loop
	for(size_t h = 0; h < height && success; ++h)
	{
		for(size_t w = 0; w < width; ++w)
		{
			try
			{
				int i = w + (h * height);
				_grid.push_back(Hex(-h, w, _hex_size, {_hex_size*2, _hex_size*4}));
#ifdef DEBUG
				cout << "Made hex ["<< i << "] at " << _grid.back();
				map_cube_to_i(_grid.back().get_cube_coords(), i);
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

Hex Hex_grid::hex_add(const Hex& a, const Hex& b)
{
	auto c_a = a.get_cube_coordinate();
	auto c_b = b.get_cube_coordinate();
	return Hex(c_a.q + c_b.q, c_a.r + c_b.r, c_a.s + c_b.s, _hex_size);
}

Hex& Hex_grid::get_hex(int q, int r, int s)
{
	size_t i = _cube_coords_to_i_map[hash_cube_coord(q,r,s)];
	return _grid[i];
}

int Hex_grid::get_hex_index(cube_coord cc)
{
	return _cube_coords_to_i_map[hash_cube_coord( get<0>(cc), get<1>(cc), get<2>(cc) )];
}

// PRIVATE MEMBERS
void Hex_grid::map_cube_to_i(Cube_coordinate cc, size_t i)
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
 
std::vector<Hex>& Hex_grid::get_grid()
{
	return _grid;
}

Orientation Hex_grid::set_orientation(Hex_orientation ho)
{
	switch(ho)
	{
		default:
		case FLAT_TOP:
			return Orientation(
					{3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0)},
					{2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0},
					0.0, ho);
			break;
		case POINTY_TOP:
			return Orientation(
					{sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0},
					{sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0},
					0.5, ho);
			break;
	}
}
