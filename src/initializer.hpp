#ifndef INITIALIZER_HPP
#define INITIALIZER_HPP

#include <functional>
class Core;
#include <string>
#include <vector>
using namespace std;
class Chai_object;

/**
 * class for initializing modules for core component.
 */

class Initializer
{
	public:
		Initializer(Core& c): _core(c){}

		void graphics(const std::string&, size_t w, size_t h);
		void events();
		void grid(size_t width, size_t height, int tile_size);
		void game_object(Chai_object& game_object);
	private:
		Core& _core;
};

#endif
