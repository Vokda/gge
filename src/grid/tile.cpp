#include "tile.hpp"
#include "../sdl_helper.hpp"

Tile::Tile(SDL_Point center_point, int size, SDL_Color c)
{
	_position = center_point;
	_color = c;
}

std::ostream& operator<<(std::ostream& ost, const Tile& tile)
{
	//SDL_Point axial = hex.cube_to_axial(cc);
	ost << "Hex " << &tile << endl;
	ost << tile.coord_to_string() << endl;
	//ost << "axial coords [" << axial.x << ", " << axial.y << "]" << endl;
	ost << "position " << tile.get_position() << endl;

	return ost;
}
