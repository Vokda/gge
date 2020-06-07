#include "initializer.hpp"

void Initializer::graphics(const std::string& s, size_t w, size_t h)
{
	_core.initialize(Core::GRAPHICS, s, w, h);
}

void Initializer::events()
{
	_core.initialize(Core::EVENT_HANDLER);
}
