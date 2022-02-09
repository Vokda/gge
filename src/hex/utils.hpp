#pragma once
#include"orientation.hpp"
#include <tuple>
using namespace std;
struct SDL_Point;
struct Cube_coordinate;

SDL_Point cube_to_evenq(const Cube_coordinate& );

Cube_coordinate evenq_to_cube(int row, int col);

typedef std::tuple<int, int, int> cube_coord;

class Utils
{
	public:
		Utils(const Layout& l);

		SDL_Point xy_to_axial(int x, int y) const;
		//SDL_Point axial_to_xy(SDL_Point p) const;
		cube_coord axial_to_cube(SDL_Point) const;

	private:
		const Layout& _layout;
		// 2x2 matrix 2x1 vector
		SDL_Point matrix_vector_mul(const std::vector<double>& m, double x, double y) const;
};
