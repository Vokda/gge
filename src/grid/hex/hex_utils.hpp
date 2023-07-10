#pragma once
#include"orientation.hpp"
#include <vector>
using namespace std;
struct SDL_Point;
struct Cube_coordinate;
struct cube_coord;
struct axial_coord;

SDL_Point cube_to_evenq(const Cube_coordinate& );


class Hex_utils
{
	public:
		Hex_utils(const Layout& l);

		axial_coord xy_to_axial(int x, int y) const;
		SDL_Point axial_to_pixel(axial_coord) const;
		axial_coord cube_to_axial(cube_coord) const;
		//SDL_Point axial_to_xy(SDL_Point p) const;
		cube_coord axial_to_cube(axial_coord) const;

		cube_coord cube_coord_round(double q, double r, double s) const;
		//void cube_coord_round(cube_coord) const;

		cube_coord offset_coord_to_cube(int col, int row) const;
		SDL_Point offset_to_pixel(cube_coord) const;

		SDL_Point calc_center_point(int col, int row) const;

	private:
		const Layout& _layout;
		// 2x2 matrix 2x1 vector
		axial_coord matrix_vector_mul(const std::vector<double>& m, double x, double y) const;
};
