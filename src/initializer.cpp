#include "initializer.hpp"
#include "core.hpp"

void Initializer::graphics(const std::string& s, size_t w, size_t h)
{
	_core.init_graphics(s.c_str(), w, h);
}

void Initializer::events()
{
	_core.init_events();
}

void Initializer::grid(size_t w, size_t h, int size)
{
	_core.init_grid(w, h, size);
}

void Initializer::game_loop(const std::function<bool(float)>& f)
{
	_core.init_game_loop(f);
}
