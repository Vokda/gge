#pragma once
#include <vector>
#include <initializer_list>
#include <SDL2/SDL.h>

struct Orientation
{
	std::vector<double> f;
	std::vector<double> b;
	const double start_angle;
	Orientation(
			std::initializer_list<double> f_i,
			std::initializer_list<double> b_i,
			double start_angle):
		f(f_i),
		b(b_i),
		start_angle(start_angle) {}
};

struct Layout
{
	const Orientation orientation;
	const SDL_Point size;
	const SDL_Point origin;
	Layout(Orientation o, SDL_Point s, SDL_Point origin): 
		orientation(o), size(s), origin(origin) {}
};
