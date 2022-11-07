#pragma once
#include "gge_module.hpp"
#include "script_handling/script_engine.hpp"
#include "core.hpp"

/*
 * a small class to call the game loop
 * script engine to call the game loop
 * core to enable quitting the game
 */
class Game_loop: public GGE_module
{
	public:
		// gge_begin export ctor
		Game_loop(Script_engine& se, Core& core);
		// gge_end export ctor
		~Game_loop() = default;

		void tick(double d);

	private:
		Script_engine& _script_engine;
		Core& _core;
};

