#include "square_utils.hpp"
#include <SDL2/SDL.h>
#include <tuple>
using namespace std;

Square_utils::Square_utils(double square_size):
	_square_size(square_size)
{

}

Square_coordinate Square_utils::pixel_to_coordinate(int x, int y) const
{
	int col = x / _square_size;
	int row = y / _square_size;
	return Square_coordinate(col, row);
}