#pragma once

#include "core.hpp"

class Initializer
{
	public:
		Initializer(Core& c): _core(c){}

		void graphics(const std::string&, size_t w, size_t h);
		void events();
	private:
		Core& _core;
};
