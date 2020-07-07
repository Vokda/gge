#pragma once

#include <functional>

/**
 * class for initializing modules for core component.
 */


class Core;
#include <string>

class Initializer
{
	public:
		Initializer(Core& c): _core(c){}

		void graphics(const std::string&, size_t w, size_t h);
		void events();
		void grid(size_t width, size_t height, int tile_size);
		void game_loop(const std::function<bool(float)>& f);
	private:
		Core& _core;
};
