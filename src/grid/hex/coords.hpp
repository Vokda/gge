#pragma once
#include <iostream>
using namespace std;

typedef std::tuple<int, int, int> cube_coord_int;

struct cube_coord
{
	double q;
	double r;
	double s;
	cube_coord(double q_, double r_, double s_):
		q(q_), r(r_), s(s_) 
	{
		double sum = q + r + s;
		if (sum != 0)
		{
			throw   "q + r + s must be 0!";
		}
	}
};

struct axial_coord
{
	double q;
	double r;

	axial_coord(double q_, double r_):
		q(q_), r(r_)
	{

	}

	axial_coord& operator *=(double x)
	{
		q *= x;
		r *= x;
		return *this;
	}
};

struct Cube_coordinate
{
	int q;
	int r;
	int s;
	Cube_coordinate(int q_, int r_, int s_):
		q(q_), r(r_), s(s_) 
	{
		int sum = q + r + s;
		if (sum != 0)
		{
			throw   "q + r + s must be 0!";
		}
	}
};

// print overloads

static std::ostream& operator<<(std::ostream& ost, const cube_coord& cc)
{
	ost << "[" << cc.q << ", " << cc.r << ", " << cc.s << "]";
	return ost;
}

/* already in sdl_helper.hpp
 * std::ostream& operator<<(std::ostream& ost, const SDL_Point& p)
{
	ost << "[" << p.x << ", " << p.y << "]";
	return ost;
}*/
