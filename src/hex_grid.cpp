#include "hex_grid.hpp"
#include "hex.hpp"

Hex_grid::Hex_grid(size_t w, size_t h, int size)
{
	// in case of square grid
	create_grid(w*h);
	_hex_size = size;
}

Hex Hex_grid::hex_add(Hex a, Hex b)
{
	auto c_a = a.get_cube_coordinate();
	auto c_b = b.get_cube_coordinate();
	return Hex(c_a.q + c_b.q, c_a.r + c_b.r, c_a.s + c_b.s, _hex_size);
}

std::vector<Hex>& Hex_grid::get_grid()
{
	return _grid;
}

void Hex_grid::create_grid(size_t size)
{
	for(size_t i = 0; i < size; ++i)
	{
		_grid.push_back(Hex(0,0,0, 0,0, _hex_size));
	}
}
