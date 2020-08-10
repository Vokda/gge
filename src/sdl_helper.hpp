#pragma once
#include <string>
#include <iostream>
#include <SDL2/SDL.h>

class SDL_helper
{
	public:
		void check_null(const std::string& check_name, const void* SDL_struct);
		void check_null(const std::string& check_name, const int SDL_result);

	private:
		void make_and_throw_exception(const std::string& error);
};

static std::ostream& operator<<(std::ostream& ost, const SDL_Point& p)
{
	ost << '[' << p.x << ", " << p.y << ']' << std::endl;
	return ost;
}
