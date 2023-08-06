#pragma once
#include <SDL2/SDL.h>
#include "coords.hpp"
#include "../tile.hpp"
#include <string>
#include "hex_utils.hpp"
#include <iostream>
#include "../../sdl_helper.hpp"

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

		// TODO should only need one of these
		const cube_coord& get_cube_coordinate() const { return _cube_coordinate; }
		const cube_coord& get_cube_coords() const { return _cube_coordinate; }

		axial_coord get_axial_coords() const { return _utils.cube_to_axial(_cube_coordinate); };


		string coord_to_string() const;
	private:
		cube_coord _cube_coordinate; // cube coordinates
		const Hex_utils& _utils;
};

static std::ostream& operator<<(std::ostream& ost, const Hex& hex)
{
	const cube_coord& cc = hex.get_cube_coords();
	ost << "Hex ";
	//ost << "offset (col, row) " << hex.get_offset_coords();
	ost << "center point (x,y)" << hex.get_position() << endl;
	ost << "cube coordinate " << cc << endl;
	ost << "axial coordinate " << hex.get_axial_coords() << endl;
	return ost;
}
