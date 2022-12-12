#include "graphics_command.hpp"

Graphics_command::Graphics_command(
		shared_ptr<GGE_module> g, 
		int command,
		shared_ptr<GGE_module> arg):
	Command(command, arg) 
{
	_graphics = static_pointer_cast<Graphics>(g);
}

void Graphics_command::execute()
{
	switch((command)_cmd)
	{
		case CLEAR_SCREEN:
			_graphics->clear_screen();
			break;
		case DRAW:
			_graphics->draw(_arg);
			break;
		case RENDER:
			_graphics->render();
			break;
		default:
			{
				string s("Graphics command not recognized: " + to_string(_cmd));
				invalid_argument ia(s);
				throw ia;
				break;
			}
	}
}

const string Graphics_command::get_command_string() const
{
	string s("Graphics->");
	switch(_cmd)
	{
		case CLEAR_SCREEN:
			s += "clear_screen()";
			break;
		case DRAW:
			s += "draw(" + _arg->get_type_string() + ")";
			break;
		case RENDER:
			s += "render()";
		default:
			return "graphics command weird";
	}
	return s;
}
