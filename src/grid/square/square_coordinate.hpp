#pragma once
#include <ostream>
#include "../tile_coordinate.hpp"
struct SDL_Point;
using namespace std;

struct Square_coordinate: public Tile_coordinate
{
    int x;
    int y;
	Square_coordinate(int x_=0, int y_=0): x(x_), y(y_) {

	}

    Square_coordinate operator+(const Square_coordinate& other) const noexcept
	{
		return Square_coordinate(x + other.x, y + other.y);
	}
	
	constexpr bool operator==(const Square_coordinate& other) const noexcept
	{
		return this->x == other.x and this->y == other.y;
	}
};

inline std::ostream& operator<<(std::ostream& ost, const Square_coordinate& sq)
{
	ost << "[" << sq.x << ", " << sq.y << "]";
	return ost;
}