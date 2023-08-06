#pragma once
#include"orientation.hpp"
#include <vector>
using namespace std;
struct SDL_Point;
struct Cube_coordinate;
#include "coords.hpp"
struct axial_coord;

SDL_Point cube_to_evenq(const Cube_coordinate& );


class Hex_utils
{
	public:
		Hex_utils(const Layout& l);

		axial_coord xy_to_axial(int x, int y) const;
		SDL_Point axial_to_pixel(axial_coord) const;
		axial_coord cube_to_axial(cube_coord) const;
		cube_coord axial_to_cube(axial_coord) const;
		cube_coord cube_coord_round(double q, double r, double s) const;
		cube_coord offset_coord_to_cube(int col, int row) const;
		SDL_Point calc_center_point(int col, int row) const;
		const vector<cube_coord>& get_relative_neighbors() const { return _relative_neighbors; };

	private:
		const Layout& _layout;
		// 2x2 matrix 2x1 vector
		axial_coord matrix_vector_mul(const std::vector<double>& m, double x, double y) const;
		const vector<cube_coord> _relative_neighbors = {
			cube_coord(0, -1, 1), // north most neighbor
			cube_coord(1, -1, 0),
			cube_coord(1, 0, -1),
			cube_coord(0, 1, -1),
			cube_coord(-1, 1, 0),
			cube_coord(-1, 0, 1)
		};
};
