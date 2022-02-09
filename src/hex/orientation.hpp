#pragma once
#include <vector>
#include <initializer_list>
#include <SDL2/SDL.h>

struct Orientation
{
	std::vector<double> f; // matrix to get screen coords
	std::vector<double> b; // matrix to get hex coords
	int orientation;
	const double start_angle;
	Orientation(
			std::initializer_list<double> f_i,
			std::initializer_list<double> b_i,
			double start_angle, int o):
		f(f_i),
		b(b_i),
		start_angle(start_angle),
		orientation(o){}
};

struct Layout
{
	const Orientation orientation;
	//const SDL_Point size;
	const double size;
	const SDL_Point origin;
	Layout(Orientation o, int s, SDL_Point origin): 
		orientation(o), size(s), origin(origin) {}
};
