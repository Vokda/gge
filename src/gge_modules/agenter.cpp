#include "agenter.hpp"
#include "spriter.hpp"
#include "../grid/tile.hpp"
#include <sstream>

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

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
#ifdef DEBUG
	cout << "Moving agent";
	cout << " to " << to;
	cout << " old sprite postion " << agent->sprite->position;
	cout << " new sprite postion " << to->get_position();
	cout << endl;
#endif 

	Move_agent move(agent, to);
	return move();
}

void Agenter::navigate(size_t agent, shared_ptr<Tile> tile)
{
	throw runtime_error("not implemented");
}

void Agenter::remove_agent(size_t a)
{
	auto agent = static_pointer_cast<Agent>(get_component(a));
	agent->permanent = false;
	agent->milliseconds = 0;
}

bool Agenter::Move_agent::operator()()
{
	auto old_tile = _agent->tile;
	// if successful move on tile was made do the rest of agent movement
	if( _agent->tile->move_agent(_agent, _tile) )
	{
		_agent->tile = _tile;
		auto pos = _agent->tile->get_position();
		return true;
	}
	else
		return false;
}

shared_ptr<Agent> Agenter::get_agent(int a)
{
	return static_pointer_cast<Agent>(get_component(a));
}
