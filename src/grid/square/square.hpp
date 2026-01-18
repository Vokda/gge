#pragma once
#include <SDL2/SDL.h>
#include "../tile.hpp"
#include <string>
#include <ostream>
#include "../../sdl_helper.hpp"
#include "square_coordinate.hpp"

class Square: public Tile
{
	public:
		Square(
				Square_coordinate,
				const SDL_Point&,
				double size,
				SDL_Color c = {255, 255, 255, 255}
		   );

		void calculate_corners(const SDL_Point& c, int s);
		SDL_Point calculate_corner(const SDL_Point& center, int, int );
		/*const Tile_coordinate& get_grid_coordinate() const { return _square_coordinate; }
		Tile_coordinate& get_grid_coordinate() { return _square_coordinate; }*/
		
		const Square_coordinate& get_grid_coordinate() const { return _square_coordinate; }

		string coordinate_to_string() const;

	private:
		Square_coordinate _square_coordinate;
};

inline std::ostream& operator<<(std::ostream& ost, const Square& square)
{
	ost << "Square ";
	ost << "center point (x,y)" << square.get_position() << endl;
	ost << "grid coordinate " << square.get_grid_coordinate() << endl;
	return ost;
}
