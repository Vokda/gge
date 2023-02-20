#include "events_command.hpp"
#include "../gge_modules/events.hpp"

Events_command::Events_command(shared_ptr<Events> module, shared_ptr<GGE_module> none):
	Command(module, none),
	_events(module) 
{}


void Events_command::execute()
{
	_events->poll_events();
}
