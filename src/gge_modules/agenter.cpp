#include "agenter.hpp"
#include "spriter.hpp"

size_t Agenter::create_agent(
		size_t tile,
		size_t sprite
		)
{
	Agent agent;
	agent.tile = tile;
	agent.sprite = sprite;

	_components.push_back(make_shared<Agent>(agent));
	return _components.size() -1;
}

void Agenter::move_agent(size_t agent, size_t tile)
{
	auto a = static_pointer_cast<Agent>(get_component(agent));
	a->tile = tile;
}

void Agenter::navigate(size_t agent, size_t tile)
{
	throw runtime_error("not implemented");
}

void Agenter::remove_agent(size_t a)
{
	auto agent = static_pointer_cast<Agent>(get_component(a));
	agent->permanent = false;
	agent->milliseconds = 0;
}

