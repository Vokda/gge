#pragma once
#include "../grid/grid.hpp"
#include "gge_module.hpp"
#include <memory>
#include <unordered_map>
using namespace std;

enum grid_type {HEX};
class Tile;

class Grider: public GGE_module
{
	public:
		Grider(grid_type gt, int width, int height, int tile_size, int x_offset, int y_offset);

		void create_grid(grid_type gt, int width, int height, int tile_size, int x, int y);

		grid_t& get_grid(){ return _grid->get_grid(); }
		const grid_t& get_grid() const{ return _grid->get_grid(); }


		shared_ptr<Tile> get_tile(int tile);
		int get_tile_index(int x, int y);
		int get_tile_index(shared_ptr<Tile>);

		const vector<int>& get_tile_neighbors_index(int tile);
		

	private:
		unique_ptr<Grid> _grid; //TODO enable to handle more than one grid
		std::unordered_map<int, vector<int>> _neighbors_indices; // cache
};
