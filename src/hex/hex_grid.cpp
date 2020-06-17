#include "hex_grid.hpp"
#include "hex.hpp"
#include <iostream>
#include "utils.hpp"
using namespace std;

Hex_grid::Hex_grid(size_t width, size_t height, int size, Hex_orientation ho):
	_hex_size(size), 
	_layout(set_orientation(ho), {1, 1}, {0, 0})
{
	// flat toped hex
	int hex_width = _hex_size * 2;
	int hex_height = _hex_size * sqrt(3);


	size_t k = 1;
	// in case of square grid
	for(size_t h = 0; h < height; ++h)
	{
		for(size_t w = 0; w < width; ++w)
		{
			try
			{
				_grid.push_back(Hex(-h, w, _hex_size, {_hex_size*2, _hex_size*4}));
				cout << "Made hex at " << _grid.back();
			}
			catch(char const* e)
			{
				cout << "Could not create grid: " << e << endl;
				break;
			}
		}
	}
}

Hex Hex_grid::hex_add(const Hex& a, const Hex& b)
{
	auto c_a = a.get_cube_coordinate();
	auto c_b = b.get_cube_coordinate();
	return Hex(c_a.q + c_b.q, c_a.r + c_b.r, c_a.s + c_b.s, _hex_size);
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
					0.0);
			break;
		case POINTY_TOP:
			return Orientation(
					{sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0},
					{sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0},
					0.5);
			break;
	}
}

