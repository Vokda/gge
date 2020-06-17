#pragma once

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
