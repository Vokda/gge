#pragma once 
#include "gge_module.hpp"
#include "componenter.hpp"

struct Sprite;

struct Agent: public Base_component
{
	size_t sprite;
	size_t tile; 
};

class Agenter: public GGE_module, public Componenter
{
	public:
		size_t create_agent(
				size_t tile,
				size_t sprite
				);

		void move_agent(size_t agent, size_t tile);
		void navigate(size_t agent, size_t tile);
		void remove_agent(size_t agent);
	private:
};
