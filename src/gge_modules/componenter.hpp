#pragma once
#include <list>
#include <memory>
#include "timer.hpp"
#include <vector>
#include "../logger.hpp"
using namespace std;

static size_t counter_id = 0;

struct Base_component
{
	virtual ~Base_component() = default;
	bool permanent;
	moment creation;
	int milliseconds;
	const size_t id = counter_id++;
};

typedef shared_ptr<Base_component> component;

/**
 * Responsible for handling components 
 * i.e. entities that can be added/removed over time
 */
class Componenter
{
	public:
		Componenter();
		virtual ~Componenter() = default;

		list<component>::iterator rm_component(list<component>::iterator itr);

		const list<component>& get_components() const { return _components; }
		vector<int> get_components_indices();

		size_t get_number_of_components() const { return _components.size(); }

		component get_component_by_id(size_t id);

		/**
		 * Will remove component right away
		 */
		void remove_component(size_t id);

		// gge_begin make commands
		virtual void tick();
		// gge_end make commands

	protected:
		component add_component(component c);
		template <typename F>
		void for_each_component(F &&f) 
		{
			for (auto &c : _components)
			{
				f(c);
			}
		}
		// returns the current time point
		moment now() { return _timer.get_time_point(); }

	private:
		Logger::Log& _componenter_log; // TODO it is inherted for some reason by agenter
		Timer _timer;
		moment _start_time; // of the object;
		list<component> _components;
		bool _list_changed = false;
		// cached list
		vector<int> _cached_indices;
};
