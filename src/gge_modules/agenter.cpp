#include "agenter.hpp"
#include "spriter.hpp"
#include "../grid/tile.hpp"
#include <sstream>

Agenter::Agenter():
	GGE_module(AGENTER) 
{
	cout << "size of list " << _components.size() << endl;
}

size_t Agenter::create_agent(
		shared_ptr<Tile> tile,
		shared_ptr<Sprite> sprite
		)
{
	if(not tile or not sprite)
	{
		stringstream ss;
		ss << "Cannot create agent without either tile and sprite being null:" << endl ;
		ss << "tile " << tile << endl;
		ss << "sprite " << sprite << endl;
		throw runtime_error(ss.str());
	}

	Agent agent;
	agent.tile = tile;
	agent.sprite = sprite;
	agent.permanent = sprite->permanent;
	agent.milliseconds = sprite->milliseconds;
	agent.creation = sprite->creation;
	agent.index = _components.size();


#ifdef DEBUG
	cout << "Creating agent";
	cout << " with sprite " << sprite;
	cout << " on tile " << tile;
	cout << " @ " << sprite->position;
	cout << endl;
#endif 
	cout << _components.size() << endl;
	_components.push_back(make_shared<Agent>(agent));
	agent.tile->place_agent(static_pointer_cast<Agent>(_components.back()));
	return _components.size() -1;
}

bool Agenter::move_agent(size_t a, shared_ptr<Tile> to)
{
	auto agent = static_pointer_cast<Agent>(get_component(a));
	_log.debugStream() << "Moving agent " << a << " to " << to 
        << " old sprite postion " << agent->sprite->position
        << " new sprite postion " << to->get_position();

	auto old_tile = agent->tile;
	// if successful move on tile was made do the rest of agent movement
	if( agent->tile->move_agent(agent, to) )
	{
		agent->tile = to;
		return true;
	}
	else
		return false;
}

void Agenter::navigate(size_t agent, shared_ptr<Tile> tile)
{
    _log.debug("agent %i & tile %i", agent, tile->coord_to_string().c_str());
	throw runtime_error("not implemented");
}

void Agenter::remove_agent(size_t a)
{
	auto agent = static_pointer_cast<Agent>(get_component(a));
	agent->permanent = false;
	agent->milliseconds = 0;
}

shared_ptr<Agent> Agenter::get_agent(int a)
{
	return static_pointer_cast<Agent>(get_component(a));
}
