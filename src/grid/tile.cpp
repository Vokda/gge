#include "tile.hpp"
#include "../gge_modules/agenter.hpp"
#include "../sdl_helper.hpp"
#include <algorithm>
#include "../gge_modules/spriter.hpp"

Tile::Tile(SDL_Point center_point, int size, SDL_Color c)
{
	_position = center_point;
	_color = c;
}

void Tile::place_agent(shared_ptr<Agent> agent)
{
	if(agent == nullptr)
		throw runtime_error("Cannot place null agent on " + coord_to_string());

	_tile_agents.push_back(agent);
	agent->tile = shared_from_this();
#ifdef DEBUG
	cout << "Agent " << agent->index << " placed on " << _position << endl;
#endif
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
	destination->place_agent(agent);
	return remove_agent(agent, false) != nullptr;
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
