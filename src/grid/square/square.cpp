#include "square.hpp"
#include <algorithm>
#include "../../sdl_helper.hpp"
#include <cmath>
using namespace std;

Square::Square(Square_coordinate sc, SDL_Point center_point, double size, SDL_Color c ): 
	Tile(center_point, size, c),
	_square_coordinate(sc)
{
	calculate_corners(_position, size);
}

void Square::calculate_corners(const SDL_Point& c, int size)
{
	_log_stream << "Calculating corners for square at " << c << " with size " << size;
	_log_stream.flush();
	int corner_distance = size * sqrt(2); // distance from center to corner pythagoran theorem
	for(int i = 0; i < 4; i++)
	{
		_corners.push_back(calculate_corner(c, corner_distance, i));
		_log_stream << "Corner " << i << ": " << _corners.back();
		_log_stream.flush();
	}
	_log_stream.flush();
}

SDL_Point Square::calculate_corner(const SDL_Point& c, int size, int i)
{
	SDL_Point p;
	double angle_deg = 90 * i + 225;
	double angle_rad = M_PI / 180 * angle_deg;
	p.x = c.x + size * std::round(cos(angle_rad));
	p.y = c.y + size * std::round(sin(angle_rad));
	return p;
}

string Square::coordinate_to_string() const
{
	ostringstream oss;
	oss << "[" << _square_coordinate.x << "," << _square_coordinate.y << "]";
	return oss.str();
}