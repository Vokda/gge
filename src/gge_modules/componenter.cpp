#include "componenter.hpp"
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif 
#include "agenter.hpp"

Componenter::Componenter():
	_componenter_log(Logger::make_category("Componenter"))
{
	_start_time = _timer.get_time_point();

}

component Componenter::add_component(component c)
{
	_list_changed = true;
	_components.push_back(c);
	return c;
}

list<component>::iterator Componenter::rm_component(list<component>::iterator itr)
{
	_componenter_log.debug("Erasing component %i", (*itr)->id);
	_list_changed = true;
	return _components.erase(itr);	
}

void Componenter::tick()
{
	//_componenter_log.debug("Componenter ticking; checking components for expiration");
	for(auto itr = _components.begin(); itr != _components.end(); ++itr)
	{
		component c = (*itr);
		if(not c->permanent)
		{
			_componenter_log.debug("Checking component %i for expiration", c->id);
			_componenter_log.debug("milli seconds: %i", c->milliseconds);
			cout << c->creation.time_since_epoch().count() << endl;
			cout << c->milliseconds << endl;
			int time_left = _timer.time_left(c->creation, c->milliseconds);
			_componenter_log.debug("Checking component for expiration - time left: %i ms", time_left);
			if(not _timer.has_time_left(c))
			{
				c = nullptr; // make sure to release the component before erasing it
				itr = _components.erase(itr);
				_componenter_log.debug("Component expired and removed");
			} 
			else if (time_left > 10000)
			{
				throw runtime_error("Component has more than 10 seconds left, something is wrong with the timer");
			}
		}
	}
}

vector<int> Componenter::get_components_indices()
{
	if(_list_changed)
	{
#ifdef DEBUG
		cout << "rebuilding components indices list" << endl;
#endif
		vector<int> ret(_components.size());
		//int i = 0;
		//for(auto c: _components)
        for(size_t i = 0; i < _components.size(); ++i)
		{
			ret[i] = i;
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

shared_ptr<Base_component> Componenter::get_component_by_id(size_t id)
{
	for(auto c: _components)
	{
		if(c->id == id)
			return c;
	}
	return nullptr;
}

void Componenter::remove_component(size_t id)
{
	for(auto itr = _components.begin(); itr != _components.end(); ++itr)
	{
		if((*itr)->id == id)
		{
			//rm_component(itr);
			(*itr)->permanent = false;
			(*itr)->milliseconds = 0;
			_componenter_log.debug("Component %i Set for removal", id);
			return;
		}
	}
	_componenter_log.debug("Available components:");
	for(auto c: _components)
	{
		_componenter_log.debug("Component %i", c->id);
	}
	throw runtime_error("Component with id " + to_string(id) + " not found");
}