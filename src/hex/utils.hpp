#pragma once
struct SDL_Point;
struct Cube_coordinate;

SDL_Point cube_to_evenq(const Cube_coordinate& );

Cube_coordinate evenq_to_cube(int row, int col);
