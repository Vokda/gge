#include "agenter.hpp"
#include "spriter.hpp"
#include "../grid/tile.hpp"
#include <sstream>

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

    _debug_stream << "Creating agent with sprite " << sprite << " on tile " << tile << " @ " << sprite->position;
    _debug_stream.flush();
	component c = add_component(make_shared<Agent>(agent));
	_debug_stream << "number of agents: " << get_number_of_components();
    _debug_stream.flush();
	agent.tile.lock()->place_agent(static_pointer_cast<Agent>(c));
	return c->id;
}

bool Agenter::move_agent(size_t a, shared_ptr<Tile> to)
{
	auto agent = static_pointer_cast<Agent>(get_component_by_id(a));
	_log.debugStream() << "Moving agent " << a << " to " << to 
        << " old sprite postion " << agent->sprite.lock()->position
        << " new sprite postion " << to->get_position();

	auto old_tile = agent->tile;
	// if successful move on tile was made do the rest of agent movement
	if (agent->tile.lock()->move_agent(agent, to))
	{
		agent->tile = to;
		return true;
	}
	else
		return false;
}

void Agenter::navigate(size_t agent, shared_ptr<Tile> tile)
{
    _log.debug("agent %i & tile %i", agent, tile->coordinate_to_string().c_str());
	throw runtime_error("agent::navigate not implemented");
}

void Agenter::remove_agent(size_t a)
{
	_log.debug("Removing agent %i", a);
	auto agent = get_agent(a);
	if(not agent)
	{
		_log.warn("Agent %i already removed!", a);
		return;
	}

	auto sprite = agent->sprite.lock();
	sprite->permanent = false;
	sprite->milliseconds = 0;

	auto tile = agent->tile.lock();
	tile->remove_agent(agent);

	remove_component(a);
}

shared_ptr<Agent> Agenter::get_agent(int a)
{
	return static_pointer_cast<Agent>(get_component_by_id(a));
}

void Agenter::tick()
{
	size_t before_tick = get_number_of_components();
	Componenter::tick();
	size_t after_tick = get_number_of_components();
	if(after_tick < before_tick)
	{
		_log.debug("Agents still existing: %i", after_tick);
	}
}