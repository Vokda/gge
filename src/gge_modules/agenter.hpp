#pragma once 
#include "gge_module.hpp"
#include "componenter.hpp"
#include <memory>

class Sprite;
class Tile;

struct Agent: public Base_component
{
	shared_ptr<Tile> tile; 
	shared_ptr<Sprite> sprite;
	size_t index;
};

class Agenter:  public Componenter, public GGE_module
{
	public:
		Agenter();
		~Agenter() = default;
		size_t create_agent(
				shared_ptr<Tile> tile,
				shared_ptr<Sprite> sprite
				);

		void move_agent(size_t agent, shared_ptr<Tile> tile);
		void navigate(size_t agent, shared_ptr<Tile> tile);
		void remove_agent(size_t agent);
};
