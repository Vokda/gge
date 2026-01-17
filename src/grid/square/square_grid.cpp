#include "square_grid.hpp"
#include "square.hpp"
#include "square_utils.hpp"
#include <stdexcept>
#include <climits>

Square_grid::Square_grid(int width, int height, double size, int x_offset, int y_offset):
	Grid(),
	_x_offset(x_offset),
	_y_offset(y_offset),
	_utils(size)
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

void Square_grid::create_grid(int width, int height, double tile_size, int x_offset, int y_offset)
{
	for(int w = 0; w < height; ++w)
	{
		for(int h = 0; h < width; ++h)
		{
				SDL_Point center_point = {int(h*tile_size),int(w*tile_size)};// _utils.calc_center_point(h, w);
				center_point.x += x_offset;
				center_point.y += y_offset;
				Square_coordinate sc{int(h),int(w)};
				shared_ptr<Square> square = make_shared<Square>(sc, center_point, tile_size);
				_grid.push_back(square);
				int i = _grid.size() - 1;
				_log_stream << "Made square ["<< i << "] at " << *square;
		}
	}
}

void Square_grid::set_tile_neighbors()
{
	// set neighbors
	for(auto tile: _grid)
	{
		shared_ptr<Square> square = static_pointer_cast<Square>(tile);
		square->set_neighbors(
				get_neighbors(
					square->get_grid_coordinate()));
	}
}

vector<shared_ptr<Tile>> Square_grid::get_neighbors(Square_coordinate sc)
{
	vector<shared_ptr<Tile>> neighbors; // at most 8 neighbors
	_log_stream << "number of neighbors of square " << Grid::get_tile(get_square_index(sc)) << ": ";
	for(auto& rel_n: _utils.get_relative_neighbors())
	{
		Square_coordinate neighbor = sc + rel_n;
		shared_ptr<Tile> i = get_square(neighbor);
		if(i) // TODO no need to recalculate every time. Cache it!
		{
			neighbors.push_back(i);
		}
	}
	_log_stream << neighbors.size(); 
	return neighbors;
}

vector<int> Square_grid::get_neighbors_index(Square_coordinate sc)
{
	vector<int> neighbors; // at most 6 neighbors
	_log_stream << "number of neighbors of square " << Grid::get_tile(get_square_index(sc)) << ": ";
	for(auto& rel_n: _utils.get_relative_neighbors())
	{
		Square_coordinate neighbor = sc + rel_n;
		int i = get_square_index(neighbor);
		if(i > -1) // TODO no need to recalculate every time. Cache it!
		{
			neighbors.push_back(i);
		}
	}
	_log_stream << neighbors.size() ;
	return neighbors;
}

shared_ptr<Square> Square_grid::get_square(const Square_coordinate& sc)
{
	int index = get_square_index(sc);
	if(index > -1)
	{
		return static_pointer_cast<Square>(_grid[index]);
	}
	else
	{
		return nullptr;
	}
}

int Square_grid::get_tile(int x, int y)
{
	x -= _x_offset;
	y -= _y_offset;
	return get_square_index(
			_utils.pixel_to_coordinate(x, y));
}

int Square_grid::get_square_index(const Square_coordinate& sc)
{
	int index = -1;
	for(size_t i = 0; i < _grid.size(); ++i)
	{
		shared_ptr<Square> square = static_pointer_cast<Square>(_grid[i]);
		if(square->get_grid_coordinate() == sc )
		{
			index = int(i);
			break;
		}
	}
	return index;
}