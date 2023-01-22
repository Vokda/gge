#include "hex.hpp"
#include <algorithm>
#include <iostream>
#include "../sdl_helper.hpp"
using namespace std;
#include <cmath>

Hex::Hex(int col, int row, cube_coord cc, SDL_Point center_point, int size, SDL_Color c ): 
	_cube_coordinate(cc), _position(center_point), _hex_color(c)
{
	calculate_corners(_position, size);
}

// Hex::~Hex() {}

/*Hex::Hex(int r, int c, int size, SDL_Point offset): 
	_cube_coordinate(evenq_to_cube(r, c))
{
	_position = hex_to_pixel(*this, size);
	_position.x += offset.x;
	_position.y += offset.y;
	if (size < 1) throw "size must be larger than 1";
	calculate_corners(_position, size);
}*/

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

/*void Hex::set_custom_data(const string& name, void* data)
{
	* 
	 * if data already exists and has different size 
	 * remove old data and replace with new data
	 *
	if(_hex_data.find(name) != _hex_data.end())
	{
		void *old_data = _hex_data[name];
		_hex_data[name] = data;
	}
}

void* Hex::get_custom_data(const string& name)
{
	return _hex_data[name];
}*/

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

std::ostream& operator<<(std::ostream& ost, const Hex& hex)
{
	auto cc = hex.get_cube_coordinate();
	//SDL_Point axial = hex.cube_to_axial(cc);
	ost << "Hex " << &hex << endl;
	ost << "cube coords [" << cc.q << ", " << cc.r << ", " << cc.s << ']' << endl;
	//ost << "axial coords [" << axial.x << ", " << axial.y << "]" << endl;
	ost << "position " << hex.get_position() << endl;

	return ost;
}
