#include "grider.hpp"
#include "../grid/hex/orientation.hpp"
#include "../grid/hex/hex_grid.hpp"

Grider::Grider(grid_type gt, int width, int height, int tile_size, int x_offset, int y_offset):
	GGE_module(GRIDER)
{
	create_grid(gt, width, height, tile_size, x_offset, y_offset);
}

void Grider::create_grid(grid_type gt, int width, int height, int tile_size, int x_offset, int y_offset)
{
	if(width < 1 or height < 1 or tile_size < 1)
	{
		stringstream ss;
		ss << "Grid paramters wrong:" << endl;
		ss << "width: " << width << endl;
		ss << "height: " << height << endl;
		ss << "tile size: " << tile_size << endl;
		ss << "offset " << x_offset << ", " << y_offset << endl;
		throw runtime_error(ss.str());
	}
	switch(gt)
	{
		case HEX:
			_grid = make_unique<Hex_grid>(width, height, tile_size, FLAT_TOP, RECT_ODD_Q, x_offset, y_offset); //TODO paramterize
			break;
		default:
			throw runtime_error("Grid type not recognized");
			break;
	}
	//return _grid.size() -1;//TODO enable to handle more than one grid
}

int Grider::get_tile_index(shared_ptr<Tile> tile)
{
	return _grid->get_tile_index(tile);
}

int Grider::get_tile_index(int x, int y)
{
	return _grid->get_tile(x, y);
}


shared_ptr<Tile> Grider::get_tile(int tile_i)
{
	return _grid->get_tile(tile_i);
}

const vector<int>& Grider::get_tile_neighbors_index(int t_i)
{
	shared_ptr<Tile> tile = get_tile(t_i);
	try
	{
		return _neighbors_indices.at(t_i);
	}
	catch(const out_of_range& oor)
	{
		// cache result
		vector<int> new_neighbors;
		for(shared_ptr<Tile> n : tile->get_neighbors())
		{
			new_neighbors.push_back(get_tile_index(n));
		}
		_neighbors_indices[t_i] = new_neighbors;
		return _neighbors_indices[t_i];
	}
}
