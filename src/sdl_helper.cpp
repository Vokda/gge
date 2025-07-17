#include "sdl_helper.hpp"

std::ostream& operator<<(std::ostream& ost, const SDL_Point& p)
{
	ost << '[' << p.x << ", " << p.y << ']';
	return ost;
}

std::ostream& operator<<(std::ostream& ost, const SDL_Rect& r)
{
	ost << '[';
	ost << r.x << ", " << r.y << ", " << r.w << ", " << r.h;
	ost << ']'; 
	return ost;
}

std::ostream& operator<<(std::ostream& ost, const SDL_Color& c)
{
	ost << '[';
	ost << (int)c.r << ", " << (int)c.g << ", " << (int)c.b << ", " << (int)c.a;
	ost << ']';
	return ost;
}

