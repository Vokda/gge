#pragma once
#include <vector>
#include <SDL2/SDL.h>

struct Cube_coordinate
{
	const int q;
	const int r;
	const int s;
};

class Hex
{
	public:
		// for hex calculations
		Hex(int q_, int r_, int s_, int size);

		// to actually create a new hex
		Hex(int q_, int r_, int s_, int x, int y, int size);

		//Hex& operator=(const Hex& h);

		const SDL_Point& get_position() { return _position; }

		//std::vector<int>& get_corners() { return _corners; }
		const std::vector<SDL_Point>& get_corners() const { return _corners; }
		const Cube_coordinate& get_cube_coordinate() const { return _cube_coordinate; }

	private:
		// cube coordinates
		Cube_coordinate _cube_coordinate;

		// position x y
		SDL_Point _position;

		std::vector<SDL_Point> _corners;

		void calculate_corners(SDL_Point& c, int s);
		SDL_Point calculate_corner(SDL_Point& center, int, int );
};
