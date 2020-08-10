#include "sdl_helper.hpp"
#include <sstream>
#include <SDL2/SDL.h>
#include <stdexcept>
using namespace std;


/*
 * check sdl return values
 * and handle it apropriately
 */
void SDL_helper::check_null(const std::string& check_name, const void * SDL_struct)
{
	cout << check_name;
	if(SDL_struct == nullptr)// or *(int*)(SDL_struct) < 0)
	{
		make_and_throw_exception(SDL_GetError());
	}
	else
	{
		cout << " - OK" <<endl;
	}
}

void SDL_helper::check_null(const std::string& check_name, const int SDL_result)
{
	cout << check_name;
	if(SDL_result < 0)
	{
		make_and_throw_exception(SDL_GetError());
	}
	else
	{
		cout << " - OK" <<endl;
	}
}

void SDL_helper::make_and_throw_exception(const std::string& error)
{
	stringstream ss;
	ss << " - SDL Error: " << error << endl;
	std::runtime_error er(ss.str());
	throw er;
}
