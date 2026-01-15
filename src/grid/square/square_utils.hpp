#pragma once
#include <vector>
using namespace std;
struct SDL_Point;
#include "square_coordinate.hpp"

class Square_utils
{
	public:
		// TODO layout param?
		Square_utils(double square_size);

		SDL_Point coord_to_pixel(Square_coordinate) const;
		Square_coordinate pixel_to_coordinate(int x, int y) const;
		SDL_Point calc_center_point(int col, int row) const;
		const vector<Square_coordinate>& get_relative_neighbors() const { return _relative_neighbors; };

	private:
		//const GGE::Layout& _layout;
		double _square_size;
		const vector<Square_coordinate> _relative_neighbors = {
			// TODO  enable to only have 4 neighbors for square grid
			Square_coordinate(0, 1), // north most neighbor
			Square_coordinate(1, 1),
			Square_coordinate(1, 0),
			Square_coordinate(1, -1),
			Square_coordinate(0, -1),
			Square_coordinate(-1, -1),
			Square_coordinate(-1, 0),
			Square_coordinate(-1, 1)
		};
};
