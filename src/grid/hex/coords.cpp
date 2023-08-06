#include "coords.hpp"

cube_coord& cube_coord::operator+=(const cube_coord& cc)
{
	if(this == &cc)
	{
		return *this;
	}
	else
	{
		q += cc.q;
		r += cc.r;
		s += cc.s;
		return *this;
	}
}

cube_coord& cube_coord::operator+(const cube_coord& cc)
{
	if(this == &cc)
	{
		return *this;
	}
	else
	{
		q += cc.q;
		r += cc.r;
		s += cc.s;
		return *this;
	}
}
