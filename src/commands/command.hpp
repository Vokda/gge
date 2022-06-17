#pragma once
#include <memory>
#include "../registered_gge_modules.hpp"
class GGE_module;
// gge_begin import commands

		enum command = {GRAPHICS_CLEAR_SCREEN, GRAPHICS_DRAW_GRID, GRAPHICS_DRAW_SHAPE, GRAPHICS_DRAW_TEXTER, GRAPHICS_RENDER, SCROLLER_SCROLL_GRID};

// gge_end import commands

class Command
{
	public:
		Command(
				std::shared_ptr<GGE_module> m, 
				rgm type,
				std::shared_ptr<GGE_module> arg,
				rgm arg_type,
				command cmd
				);

		bool setup(std::shared_ptr<GGE_module> arg);
	

		// do nothing unless defined
		virtual void execute() {};

		// gge_begin string_commands
		static command from_string(const std::string& str)
		{
			return GRAPHICS_RENDER;
		}
		// gge_end strin_commands
	protected:
		std::shared_ptr<GGE_module> _module; // caller
		rgm _type_m; // type of _module

		std::shared_ptr<GGE_module> _arg; // might be used as argument by caller
		rgm _type_a; // type of argument
};
