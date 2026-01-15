#include "grid.hpp"
#include <stdexcept>
#include <algorithm>
using namespace std;

Grid::Grid():
    _log(Logger::make_category("Base Grid")),
	_log_stream(Logger::make_category_stream(log4cpp::Priority::DEBUG, "Grid"))
{
}

shared_ptr<Tile> Grid::get_tile(size_t i)
{
	if(is_legal_tile(i))
	{
		return _grid[i];
	}
	else
	{
        _log.fatal("Cannot access hex %s! Out of range for grid (0-%s)",
                to_string(i), to_string(_grid.size()-1)
                );
		throw out_of_range("Tile outside of range!");
	}
}

bool Grid::is_legal_tile(size_t i )
{
	return i < _grid.size();
}

int Grid::get_tile_index(shared_ptr<Tile> t)
{
    _log.debug("Searching for tile index for %i =>", t );
	auto itr = std::find(_grid.begin(), _grid.end(), t);
	int out = -1;
	if(itr != _grid.end())
	{
		out = std::distance(_grid.begin(), itr);
        _log.debug("found %i", out);
	}
	else
    {
        _log.debug("NOT found!");
	}
	return out;
}
