#include "componenter.hpp"
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif 

void* Componenter::add_component(component c)
{
	_list_changed = true;
	_components.push_back(c);
	return c.get();
}

list<component>::iterator Componenter::rm_component(list<component>::iterator itr)
{
	_list_changed = true;
	return _components.erase(itr);	
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
	for(itr = _components.begin(); itr != _components.end() and counter < i; ++itr)
	{
		++counter;
	}
#ifdef DEBUG
	if(itr == _components.end())
	{
		cout << "counter " << counter << endl;
		cout << "component "<< i << " not found" << endl;
		cout << "components available: " << _components.size() << endl;
	}
#endif
	return itr != _components.end() ? (*itr) : nullptr;
}

vector<int> Componenter::get_components_indices()
{
	if(_list_changed)
	{
#ifdef DEBUG
		cout << "rebuilding components indices list" << endl;
#endif
		vector<int> ret(_components.size());
		int i = 0;
		for(auto c: _components)
		{
			ret[i] = i++;
		}
		_list_changed = false;
		_cached_indices = ret;
		return _cached_indices;
	}
	else
	{
#ifdef DEBUG
		cout << "using cached components indices list" << endl;
#endif
		return _cached_indices;
	}
}

