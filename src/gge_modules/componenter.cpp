#include "componenter.hpp"
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif 

void* Componenter::add_component(component c)
{
	_components.push_back(c);
	return c.get();
}

void Componenter::tick()
{
	for(auto itr = _components.begin(); itr != _components.end(); ++itr)
	{
		component c = (*itr);
		if(not c->permanent)
		{
			int time_left = _timer.time_left(c->creation, c->milliseconds);
			if(time_left <= 0)
			{
				itr = _components.erase(itr);
			}
		}
	}
}

component Componenter::get_component(size_t i)
{
	list<component>::iterator itr;
	size_t counter = 0;
	for(itr = _components.begin(); itr != _components.end() or counter < i; ++itr)
	{
		++counter;
	}
	return (*itr);
}
