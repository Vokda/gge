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
	agent->sprite.lock()->set_position(_position);
	replace_agents();
    _log.debug("Agent %i placed @ [%i, %i]", agent->id, _position.x, _position.y);
}

void Tile::remove_agent(shared_ptr<Agent> agent)
{
	auto agent_itr = find_if(
		_tile_agents.begin(),
		_tile_agents.end(),
		[agent](const weak_ptr<Agent> &a)
		{
			auto target = agent;
			auto agent_ptr = a.lock();
			return agent_ptr && agent_ptr->id == target->id; 
		});
	if(agent_itr != _tile_agents.end())
	{
		_log.debug("Removing agent %i from tile %s", agent->id, coordinate_to_string().c_str());
		_tile_agents.erase(agent_itr);
	}
	else
		throw runtime_error("Cannot remove agent " + to_string(agent->id) + " from tile " + coordinate_to_string() + " because it is not on the tile!");
}

bool Tile::move_agent(shared_ptr<Agent> agent, shared_ptr<Tile> destination)
{
    _log_stream << "moving agent " << agent->id << " @ " << destination->get_position();
	destination->place_agent(agent);
	remove_agent(agent);
	return true;
}

void Tile::replace_agents()
{
	int nr_agents = _tile_agents.size();
	if(nr_agents == 1)
	{
		_log.debug("only one agent on tile %s, no need to replace", coordinate_to_string().c_str());
		return;
	}
	else 
	{
		_log.debug("replacing %i agents on tile %s", nr_agents, coordinate_to_string().c_str());
	}

	// if more than one agent per tile to rearrange them in a circular pattern
	int i = 0;
	for(weak_ptr<Agent> a : _tile_agents)
	{
		auto agent = a.lock();
		int x = int(_position.x - (_size/2) *(sin(i)));
		int y = int(_position.y - (_size/2) *(cos(i))) ;
		agent->sprite.lock()->set_position({
				x, 
				y
				});
		++i;
		_log.debug("Agent %i replaced @ [%i, %i]", agent->id, x, y);
	}
	_log.debug("agents on tile %i", nr_agents);
}

const vector<weak_ptr<Tile>>& Tile::get_neighbors() const
{
	return _neighbors;
}