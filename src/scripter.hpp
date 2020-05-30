#pragma once
#include <chaiscript/chaiscript.hpp>

class Scripter
{
	public:
		Scripter(const std::string& filename);

	private:
		chaiscript::ChaiScript _chai;

};
