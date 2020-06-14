#include "sdl_init_helper.hpp"
#include <iostream>
#include <SDL2/SDL.h>
using namespace std;


/*
 * check sdl return values
 * and handle it apropriately
 */
void check_null(const std::string& check_name, const void * SDL_struct)
{
	cout << check_name;
	if(SDL_struct == nullptr)// or *(int*)(SDL_struct) < 0)
	{
		cerr << " - SDL Error: " << SDL_GetError() << endl;
		throw 1;
	}
	else
	{
		cout << " - OK" <<endl;
	}
}

void check_null(const std::string& check_name, const int SDL_result)
{
	cout << check_name;
	if(SDL_result < 0)
	{
		cerr << " - SDL Error: " << SDL_GetError() << endl;
		throw 1;
	}
	else
	{
		cout << " - OK" <<endl;
	}
}

