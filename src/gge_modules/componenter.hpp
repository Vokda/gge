#pragma once
#include <list>
#include <memory>
#include "timer.hpp"
#include <vector>
using namespace std;

struct Base_component
{
	bool permanent;
	moment creation;
	int milliseconds;
};

typedef shared_ptr<Base_component> component;

class Componenter
{
	public:
		Componenter() = default;
		virtual ~Componenter() = default;

		/*
		 * returns memory address of t
		 * to be used to refer to specific text
		 */
		void* add_component(component c);
		list<component>::iterator rm_component(list<component>::iterator itr);

		const list<component>& get_components() const { return _components; }
		vector<int> get_components_indices();

		component get_component(size_t i);

		// gge_begin make commands
		void tick();
		// gge_end make commands

	protected:
		Timer _timer;
		moment _start_time; // of the object;
		list<component> _components;
		bool _list_changed = false;
		// cached list
		vector<int> _cached_indices;
};
