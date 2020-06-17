#include "utils.hpp"
#include <SDL2/SDL.h>
#include "cube_coordinate.hpp"

SDL_Point cube_to_evenq(const Cube_coordinate& cube)
{
    return {cube.q, (cube.s + (cube.q + cube.q&1)) / 2};
}

Cube_coordinate evenq_to_cube(int r, int c)
{
    int x = c;
    int z = r - (c + (c&1)) / 2;
    int y = -x-z;
    return {x, y, z};
}
