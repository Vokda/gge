#pragma once
#include <iostream>
#include <SDL2/SDL.h>

class SDL_helper
{
	public:
		void check_null(const std::string& check_name, const void* SDL_struct);
		void check_null(const std::string& check_name, const int SDL_result);

	private:
		void make_and_throw_exception(
				const std::string& check_name, 
				const std::string& error);
};

static std::ostream& operator<<(std::ostream& ost, const SDL_Point& p)
{
	ost << '[' << p.x << ", " << p.y << ']';
	return ost;
}

static std::ostream& operator<<(std::ostream& ost, const SDL_Rect& r)
{
	ost << '[';
	ost << r.x << ", " << r.y << ", " << r.w << ", " << r.h;
	ost << ']'; 
	return ost;
}

static std::ostream& operator<<(std::ostream& ost, const SDL_Color& c)
{
	ost << '[';
	ost << (int)c.r << ", " << (int)c.g << ", " << (int)c.b << ", " << (int)c.a;
	ost << ']';
	return ost;
}
