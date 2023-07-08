#pragma once
#include "../grid/grid.hpp"
#include "gge_module.hpp"
#include <memory>
using namespace std;

enum grid_type {HEX};

class Grider: public GGE_module
{
	public:
		Grider(grid_type gt, int width, int height, int tile_size, int x_offset, int y_offset);

		void create_grid(grid_type gt, int width, int height, int tile_size, int x, int y);

		grid_t& get_grid(){ return _grid->get_grid(); }
		const grid_t& get_grid() const{ return _grid->get_grid(); }


		size_t get_tile(int x, int y);

	private:
		unique_ptr<Grid> _grid; //TODO enable to handle more than one grid
};
