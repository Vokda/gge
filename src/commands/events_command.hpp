#pragma once
#include "command.hpp"
#include <memory>
#include <string>
#include "../gge_modules/events.hpp"
using namespace std;

class Events_command: public Command
{
	public:
		Events_command(shared_ptr<Events> module, shared_ptr<GGE_module> none);
		void execute();
		const string get_command_string() const { return "_events->poll_events()"; }

	private:
		shared_ptr<Events> _events;
};
