#include "hex.hpp"
#include <algorithm>
#include "../../sdl_helper.hpp"
#include <cmath>
using namespace std;

Hex::Hex(cube_coord cc, SDL_Point center_point, int size, Hex_utils& hu, SDL_Color c ): 
	Tile(center_point, size, c),
	_cube_coordinate(cc),
	_utils(hu)
{
	calculate_corners(_position, size);
}

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

string Hex::coord_to_string() const
{
	stringstream ss;
	ss << "hex cube coordinate " << _cube_coordinate << endl;
	SDL_Point p = _utils.axial_to_pixel(_utils.cube_to_axial(_cube_coordinate));
	ss << "hex xy coordinate " << p << endl;
	return ss.str();
}
