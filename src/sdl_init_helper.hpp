#pragma once
#include <string>

/*
 * just a few functions for helping when initializing sdl stuff
 */

void check_null(const std::string& check_name, const void* SDL_struct);
void check_null(const std::string& check_name, const int SDL_result);
