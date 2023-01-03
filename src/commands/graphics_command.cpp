#include "graphics_command.hpp"

Graphics_command::Graphics_command(
		shared_ptr<GGE_module> g, 
		shared_ptr<GGE_module> arg,
		int command
		):
	Command(g,  arg, command) 
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
			break;
		default:
			return "graphics command weird! cmd: " + to_string(_cmd);
	}
	return s;
}

bool Graphics_command::is_valid_command() const
{
	return _cmd < NR_COMMANDS and _cmd > -1;
}
