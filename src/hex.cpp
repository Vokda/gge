#include "hex.hpp"
#include <algorithm>
#include <cmath>

Hex::Hex(int q, int r, int s, int size): 
	_cube_coordinate({q, r, s})
{
	if (q + r + s != 0) throw "q + r + s must be 0";
	//calculate_corners(_position, size);
}

Hex::Hex(int q, int r, int s, int x, int y, int size): 
	_cube_coordinate({q, r, s}),
	_position({x,y})
{
	if (q + r + s != 0) throw "q + r + s must be 0";
	calculate_corners(_position, size);
}


void Hex::calculate_corners(SDL_Point& c, int size)
{
	for(int i = 0; i < 6; i++)
	{
		_corners.push_back(
				calculate_corner(c, size, i)
				);
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
