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

	return _components.size() -1;
}

void Agenter::move_agent(size_t a, shared_ptr<Tile> to)
{
	auto agent = static_pointer_cast<Agent>(get_component(a));
	auto from = agent->tile;
	from->move_agent(agent, to);
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

