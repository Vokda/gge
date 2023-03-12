#include "grid.hpp"
#include "../gge_modules/registered_gge_modules.hpp" // TODO to get throw_message, move to some other class for this 
#include <stdexcept>
using namespace std;

shared_ptr<Tile> Grid::get_tile(size_t i)
{
	if(is_legal_tile(i))
	{
		return _grid[i];
	}
	else
	{
		throw out_of_range(throw_message(
					__FILE__, 
					"cannot access hex " + to_string(i) + "! Out of range for grid (0-"+to_string(_grid.size()-1)+")",
					GRIDER));
	}
}

bool Grid::is_legal_tile(size_t i )
{
	return i >= 0 and i < _grid.size();
}

