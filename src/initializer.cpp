#include "initializer.hpp"
#include "core.hpp"
#include "chai_object.hpp"
#include <utility>

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

void Initializer::game_object(Chai_object& game_object)
{
	_core.init_game_object(forward<Chai_object>(game_object));
}

const Core& Initializer::get_core() const
{
	return _core;
}

Core& Initializer::get_core()
{
	return _core;
}
