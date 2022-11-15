#pragma once
#include "command.hpp"
#include <memory>
#include "../events.hpp"
#include <string>
using namespace std;

class Events_command: public Command
{
	public:
		Events_command(shared_ptr<Events> module);
		void execute();
		const string get_command_string() const { return "_events->poll_events()"; }

	private:
		shared_ptr<Events> _events;
};