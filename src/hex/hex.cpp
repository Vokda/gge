#include "hex.hpp"
#include <algorithm>
#include <iostream>
#include "../sdl_init_helper.hpp"
#include "utils.hpp"
using namespace std;
#include <cmath>

Hex::Hex(int q, int r, int s, int size): 
	_cube_coordinate({q, r, s})
{
	if (q + r + s != 0) throw "q + r + s must be 0";
	//calculate_corners(_position, size);
}

Hex::Hex(int r, int c, int size, SDL_Point offset): 
	_cube_coordinate(evenq_to_cube(r, c))
{
	_position = hex_to_pixel(*this, size);
	_position.x += offset.x;
	_position.y += offset.y;
	if (size < 1) throw "size must be larger than 1";
	calculate_corners(_position, size);
}

/*
SDL_Point Hex::hex_to_pixel(const Hex& hex)
{
	return
	{
		_hex_size * (3.0/2.0 * hex.q),
		_hex_size * (sqrt(3)/2.0 * hex.q + sqrt(3) * hex.r)
	};
}
*/


void Hex::calculate_corners(SDL_Point& c, int size)
{
	for(int i = 0; i < 6; i++)
	{
		_corners.push_back(calculate_corner(c, size, i));
	}
}

SDL_Point Hex::calculate_corner(SDL_Point& c, int size, int i)
{
	SDL_Point p;
	double angle_deg = 60 * i;
	double angle_rad = M_PI / 180 * angle_deg;
	p.x = c.x + size * cos(angle_rad);
	p.y = c.y + size * sin(angle_rad);
	return p;
}

/*
Hex& Hex::operator=(const Hex& other)
{
	if(&other == this)
		return *this;
	_cube_coordinate = other.get_cube_coordinate();
	_position = other.get_position();
	auto corners = other.get_corners();
	std::copy(corners.begin(), corners.end(), _corners.begin());
	return *this;
}
*/


Cube_coordinate Hex::axial_to_cube(const Hex& h) const
{
	auto cc = get_cube_coordinate();
    return Cube_coordinate(cc.q, cc.r, -cc.q - cc.r);
}

Cube_coordinate Hex::axial_to_cube(int q, int r) const
{
    return Cube_coordinate(q, r, -q - r);
}

SDL_Point Hex::cube_to_axial(const Cube_coordinate& cc) const
{
	return 
	{
		cc.q,
		cc.r
	};
}
//
// only flat-top atm
SDL_Point Hex::hex_to_pixel(const Hex& h, int size)
{
	auto cc = h.get_cube_coordinate();
	return 
	{
		int(round(size * (3.0/2.0 * cc.q))),
		  int(round(size * (sqrt(3)/2.0 * cc.q + sqrt(3) * cc.r)))
	};
}

std::ostream& operator<<(std::ostream& ost, const Hex& hex)
{
	auto cc = hex.get_cube_coordinate();
	SDL_Point axial = hex.cube_to_axial(cc);
	ost << "Hex " << &hex << endl;
	ost << "cube coords [" << cc.q << ", " << cc.r << ", " << cc.s << ']' << endl;
	ost << "axial coords [" << axial.x << ", " << axial.y << "]" << endl;
	ost << "position " << hex.get_position() << endl;

	return ost;
}
