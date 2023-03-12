#pragma once
#include <vector>
#include <SDL2/SDL.h>

enum Hex_orientation {FLAT_TOP, POINTY_TOP};
/*
 * RECT = rectangular map layout
 * ODD or EVEN q (columns) or r(rows) are offset
 */
enum Coordinate_system {RECT_ODD_Q};//more to come

struct Orientation
{
	std::vector<double> f; // matrix to get screen coords
	std::vector<double> b; // matrix to get hex coords
	Hex_orientation orientation;
	double start_angle;
	double hex_radius; // aka size, distance from center point to corner
	double hex_width;
	double hex_height;

	Orientation(Hex_orientation o, double size):
		orientation(o)
	{
		hex_radius = size;
		switch(o)
		{
			case FLAT_TOP:
				f = {3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0)};
				b = {2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0};
				start_angle = 0.0;
				hex_width = 2 * size;
				hex_height = sqrt(3) * size;
				break;
			case POINTY_TOP:
				f = {sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0};
				b = {sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0};
				start_angle = 0.5; 
				hex_height = 2 * size;
				hex_width = sqrt(3) * size;
				break;
		}
	}
};

struct Layout
{
	const Orientation orientation; // hex orientation
	const Coordinate_system coordinate_system;
	const double& size; // ref to orientation.hex_radius for legacy reason
	Layout(Orientation o, Coordinate_system coord_sys): 
		orientation(o), coordinate_system(coord_sys), size(orientation.hex_radius)
		{}
};
