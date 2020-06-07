#include "core.hpp"
#include "graphics.hpp"
#include <cstdarg>

void Core::initialize(Module m, ...)
{
	va_list args;
	switch(m)
	{
		case GRAPHICS:
			{
				auto s = va_arg(args, const std::string);
				auto w = va_arg(args, size_t);
				auto h = va_arg(args, size_t);
				_graphics = std::shared_ptr<Graphics>(new Graphics(s, w, h));
				break;
			}
		case EVENT_HANDLER:
			;
			break;
	}
}
