#include "initializer.hpp"
#include "core.hpp"

void Initializer::graphics(const std::string& s, size_t w, size_t h)
{
	_core.initialize(Core::GRAPHICS, s, w, h);
}

void Initializer::events()
{
	_core.initialize(Core::EVENT_HANDLER);
}

void Initializer::grid(size_t w, size_t h, int size)
{
	_core.initialize(Core::GRID, w, h, size);
}

void Initializer::game_loop(const std::function<bool(float)>& f)
{
	_core.initialize(Core::GAME_LOOP, f);
}
