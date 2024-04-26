#pragma once

#include <vector>
#include <unordered_map>

//class Hex;
#include "hex.hpp"
#include "orientation.hpp"
#include "../grid.hpp"


using namespace std;

class Hex_grid: public Grid
{
	public:

		Hex_grid(size_t w, size_t h, double hex_size, GGE::Hex_orientation ho, GGE::Coordinate_system cs, int x_offset, int y_offset);
		//Hex_grid(const Hex_grid& hg);

		//Hex hex_add(const Hex& a, const Hex& b);

		/*Hex get_hex(int q, int  r, int s);
		Hex& get_hex(size_t i);*/
		/**
		 * return -1 if no hex with that index is found
		 */
		int get_hex_index(cube_coord c);
		shared_ptr<Hex> get_hex(cube_coord cc);
		int get_tile(int mouse_x, int mouse_y);

	private:
		// used to map qrs coords to index in vector
		typedef std::unordered_map<int, int> cube_coords_map;
		cube_coords_map _cube_coords_to_i_map;

		void map_cube_to_i(cube_coord, size_t i);
		int hash_cube_coord(int q, int r, int s);

		vector<int> get_neighbors_index(cube_coord cc);
		vector<shared_ptr<Tile>> get_neighbors(cube_coord cc);

		// vars
        GGE::Layout _layout;
		int _x_offset = 0;
		int _y_offset = 0;
		
		/* ugly special case for the gge api 
		 * so you can do something like
		 * grid = core.get_grid()
		 * grid->_utils.<grid_related stuff>();
		 */
		Hex_utils _utils;
};
