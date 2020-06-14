#pragma once

#include <memory>
#include "graphics.hpp"
#include "events.hpp"
#include "hex_grid.hpp"

class Core
{
	public:
		Core() = default;

		enum Module {GRAPHICS, AUDIO, EVENT_HANDLER, GRID, NR_MODULES};
		void initialize(Module m, ...);

		// fix soon
		bool handle_events();

		void check_modules_initiated();
		void render(bool clear_scrn);
		void grid(size_t w, size_t h);

	private:


		void game_loop();

		std::shared_ptr<Graphics> _graphics;
		std::shared_ptr<Events> _events;
		std::shared_ptr<Hex_grid> _grid;


};
