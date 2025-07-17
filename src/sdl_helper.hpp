#pragma once
#include <iostream>
#include <SDL2/SDL.h>

std::ostream& operator<<(std::ostream& ost, const SDL_Point& p);

std::ostream& operator<<(std::ostream& ost, const SDL_Rect& r);

std::ostream& operator<<(std::ostream& ost, const SDL_Color& c);
