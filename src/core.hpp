#pragma once

#include <memory>
#include "graphics.hpp"

class Core
{
	public:
		Core() = default;

		enum Module {GRAPHICS, AUDIO, EVENT_HANDLER, NR_MODULES};
		void initialize(Module m, ...);

	private:
		std::shared_ptr<Graphics> _graphics;
		//std::shared_ptr<> _graphics;
		//init_graphics(const std::string& window_name, size_t width, size_t height); 
};
