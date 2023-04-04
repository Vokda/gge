#include "tile.hpp"
#include "../gge_modules/agenter.hpp"
#include "../sdl_helper.hpp"
#include <algorithm>

Tile::Tile(SDL_Point center_point, int size, SDL_Color c)
{
	_position = center_point;
	_color = c;
}

void Tile::place_agent(shared_ptr<Agent> agent)
{
	throw runtime_error("Cannot place null agent on " + coord_to_string());
	_tile_agents.push_back(agent);
	agent->tile = shared_from_this();
}

shared_ptr<Agent> Tile::remove_agent(shared_ptr<Agent> agent)
{
	auto agent_itr = find(_tile_agents.begin(), _tile_agents.end(), agent);
	_tile_agents.erase(agent_itr);
	agent->tile = nullptr;
	return agent_itr != _tile_agents.end() ? (*agent_itr) : nullptr;
}

bool Tile::move_agent(shared_ptr<Agent> agent, shared_ptr<Tile> destination)
{
	auto tmp_agent = this->remove_agent(agent);
	if(tmp_agent == nullptr)
		return false;
	destination->place_agent(agent);
	return true;
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
