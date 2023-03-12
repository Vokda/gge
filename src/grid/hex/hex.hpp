#pragma once
#include <SDL2/SDL.h>
#include "coords.hpp"
#include "../tile.hpp"
#include <string>
#include "hex_utils.hpp"

class Hex: public Tile
{
	public:
		Hex(
				cube_coord, 
				SDL_Point,
				int size,
				Hex_utils&,
				SDL_Color c = {255, 255, 255, 255}
		   );

		void calculate_corners(SDL_Point& c, int s);
		SDL_Point calculate_corner(SDL_Point& center, int, int );

		const cube_coord& get_cube_coordinate() const { return _cube_coordinate; }
		cube_coord get_cube_coords() { return _cube_coordinate; }

		string coord_to_string() const;
	private:
		cube_coord _cube_coordinate; // cube coordinates
		const Hex_utils& _utils;
};
