#include "utils.hpp"
#include <SDL2/SDL.h>
#include "cube_coordinate.hpp"
#include <tuple>
using namespace std;

SDL_Point cube_to_evenq(const Cube_coordinate& cube)
{
    return {cube.q, (cube.s + (cube.q + cube.q&1)) / 2};
}

Cube_coordinate evenq_to_cube(int r, int c)
{
    int x = c;
    int z = r - (c + (c&1)) / 2;
    int y = -x-z;
    return {x, y, z};
}

Utils::Utils(const Layout& o):
	_layout(o)
{
}

SDL_Point Utils::xy_to_axial(int x, int y) const
{
	//b_i * x y / size = q r
	SDL_Point axial = matrix_vector_mul(_layout.orientation.b, x, y);
	double size = _layout.size;
	axial.x /= size;
	axial.y /= size;
	return axial;
}

SDL_Point Utils::matrix_vector_mul(const std::vector<double>& m, double x, double y) const
{
	SDL_Point r; 
	r.x = m[0] * x + m[1] * y;
	r.y = m[2] * x + m[3] * y;
	return r;
}

cube_coord Utils::axial_to_cube(SDL_Point p) const
{
	cube_coord cc(p.x, p.y, -p.x-p.y);
	return cc;
}
