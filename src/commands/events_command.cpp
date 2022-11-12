#include "events_command.hpp"

Events_command::Events_command(shared_ptr<Events> module):
	_events(module) 
{}


void Events_command::execute()
{
	_events->poll_events();
}
