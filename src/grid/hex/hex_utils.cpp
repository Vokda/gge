#include "hex_utils.hpp"
#include <SDL2/SDL.h>
#include "coords.hpp"
#include <tuple>
using namespace std;

SDL_Point cube_to_evenq(const Cube_coordinate& cube)
{
    return {cube.q, (cube.s + (cube.q + cube.q&1)) / 2};
}

Hex_utils::Hex_utils(const Layout& o):
	_layout(o)
{
}

axial_coord Hex_utils::xy_to_axial(int x, int y) const
{
	//b_i * x y / size = q r
	axial_coord axial = matrix_vector_mul(_layout.orientation.b, x, y);
	double size = _layout.size;
	axial.q /= size;
	axial.r /= size;
	return axial;
}

axial_coord Hex_utils::matrix_vector_mul(const std::vector<double>& m, double x, double y) const
{
	return {m[0] * x + m[1] * y, m[2] * x + m[3] * y};
}

cube_coord Hex_utils::axial_to_cube(axial_coord p) const
{
	cube_coord cc(cube_coord_round(p.q, p.r, -p.q-p.r));
	return cc;
}

cube_coord Hex_utils::cube_coord_round(double q, double r, double s) const
{
	int iq = round(q);
	int ir = round(r);
	int is = round(s);

	double q_diff = abs(iq - q);
	double r_diff = abs(ir - r);
	double s_diff = abs(is - s);

	if( q_diff > r_diff and q_diff > s_diff)
	{
		iq = -ir-is;
	}
	else if( r_diff > s_diff )
	{
		ir = -iq-is;
	}
	else
	{
		is = -iq-ir;
	}

	return cube_coord(iq, ir, is);
}

axial_coord Hex_utils::cube_to_axial(cube_coord cc) const
{
	return {cc.q, cc.r};
}

SDL_Point Hex_utils::axial_to_pixel(axial_coord ac) const
{
	axial_coord tac = matrix_vector_mul(_layout.orientation.b, ac.q, ac.r);
	tac *= _layout.size;
	return {(int)tac.q, (int)tac.r};
}

cube_coord Hex_utils::offset_coord_to_cube(int col, int row) const
{
	double q = col;
	double r = row;
	switch(_layout.coordinate_system)
	{
		case(RECT_ODD_Q):
			r = row - (col - (col&1)) / 2;
			break;
		default: 
			throw runtime_error("ERROR coordinate system not implemented");
	}
	return cube_coord(q, r, -q-r);
}

SDL_Point Hex_utils::calc_center_point(cube_coord cc) const
{
	//SDL_Point p = axial_to_pixel(cube_to_axial(cc));
	SDL_Point p;
	int col = cc.q;
	int row = cc.r;
	switch(_layout.coordinate_system)
	{
		case(RECT_ODD_Q):
			// odd columns move down
			p.x = _layout.size * _layout.orientation.f[0] * col;
			p.y = _layout.size * _layout.orientation.f[3] * (row + 0.5 * (col&1));
			break;
		default: 
			throw runtime_error("ERROR coordinate system not implemented");
	}
#ifdef DEBUG
#include <iostream>
	cout << "Center point: " << cc << " -> " << p.x << ',' << p.y << endl;
#endif
	return p;
}

SDL_Point Hex_utils::offset_to_pixel(cube_coord cc) const
{
	SDL_Point p;
	p.x = 0;
	p.y = 0;
	return p;
}
