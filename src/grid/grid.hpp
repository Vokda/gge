#pragma once
#include <vector>
#include <memory>
using namespace std;
#include "tile.hpp"

using grid_t = vector<shared_ptr<Tile>>;

class Grid
{
	public:
		Grid() = default;
		virtual ~Grid() = default;


		shared_ptr<Tile> get_tile(size_t i);
		int get_tile_index(shared_ptr<Tile> t);

		// getters
		grid_t& get_grid() { return _grid; };
		const grid_t& get_grid() const { return _grid; }

		/**
		 * return index of tile based on mouse position
		 * return -1 if no hex with that index is found
		 */
		int virtual get_tile(int mouse_x, int mouse_y) = 0;

	protected:
		bool is_legal_tile(size_t i);

		grid_t _grid;
		int tile_size;
};
