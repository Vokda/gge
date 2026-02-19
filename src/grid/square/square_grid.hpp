#pragma once

#include <vector>
#include <unordered_map>
#include "square.hpp"
#include "../grid.hpp"
#include "square_utils.hpp"
struct Square_coordinate;

using namespace std;

class Square_grid: public Grid
{
	public:

		Square_grid(int w, int h, double square_size, int x_offset, int y_offset);

		void create_grid(int width, int height, double tile_size, int x_offset, int y_offset);
		void set_tile_neighbors();
		/**
		 * return -1 if no hex with that index is found
		 */
		int get_square_index(const Square_coordinate& sc);
		int get_tile(int x, int y);
		int get_tile_index_from_coordinate(int x, int y);
		shared_ptr<Square> get_square(const Square_coordinate& sc);

	private:
		// used to map qrs coords to index in vector
		typedef std::unordered_map<int, int> cube_coords_map;

		vector<int> get_neighbors_index(Square_coordinate sc);
		vector<weak_ptr<Tile>> get_neighbors(Square_coordinate sc);

		// vars
		int _x_offset = 0;
		int _y_offset = 0;
		Square_utils _utils;
};
