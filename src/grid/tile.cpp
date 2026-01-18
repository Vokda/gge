#include "tile.hpp"
#include "../gge_modules/agenter.hpp"
#include "../sdl_helper.hpp"
#include <algorithm>
#include "../gge_modules/spriter.hpp"
#include <cmath>

Tile::Tile(SDL_Point center_point, int size, SDL_Color c):
    _logger(Logger::get_instance()),
    _log(_logger.add_category("Tile", log4cpp::Priority::DEBUG)),
    _log_stream(_logger.make_category_stream(log4cpp::Priority::DEBUG, "Tile"))

{
	_position = center_point;
	_color = c;
	_size = size;
}

void Tile::place_agent(shared_ptr<Agent> agent)
{
	if(agent == nullptr)
		throw runtime_error("Cannot place null agent on " + coordinate_to_string());

	_tile_agents.push_back(agent);
	agent->tile = shared_from_this();
	replace_agents();
    _log.debug("Agent %i placed @ [%i, %i]", agent->index, _position.x, _position.y);
}

shared_ptr<Agent> Tile::remove_agent(shared_ptr<Agent> agent, bool completely)
{
	auto agent_itr = find(_tile_agents.begin(), _tile_agents.end(), agent);
	_tile_agents.erase(agent_itr);
	if(completely)
		agent->tile = nullptr;
	return agent_itr != _tile_agents.end() ? (*agent_itr) : nullptr;
}

bool Tile::move_agent(shared_ptr<Agent> agent, shared_ptr<Tile> destination)
{
    _log_stream << "moving agent " << agent->index << " @ " << destination->get_position();
	destination->place_agent(agent);
	return remove_agent(agent, false) != nullptr;
}

void Tile::replace_agents()
{
	int nr_agents = _tile_agents.size();
	if(nr_agents == 1)
		return;

	// if more than one agent per tile to rearrange them in a circular pattern
	int i = 0;
	for(auto agent : _tile_agents)
	{
		int x = int(_position.x - (_size/2) *(sin(i)));
		int y = int(_position.y - (_size/2) *(cos(i))) ;
		agent->sprite->set_position({
				x, 
				y
				});
		++i;
#ifdef DEBUG
	cout << "Agent " << agent->index << " replaced at  " << agent->sprite->position << endl;
#endif
	}
	cout << "agents on tile " << nr_agents << endl;
}

const vector<shared_ptr<Tile>>& Tile::get_neighbors() const
{
	return _neighbors;
}