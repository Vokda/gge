#pragma once 
#include "gge_module.hpp"
#include "componenter.hpp"
#include <memory>

struct Sprite;
class Tile;

struct Agent: public Base_component
{
	weak_ptr<Tile> tile; 
	weak_ptr<Sprite> sprite;
};

class Agenter: public Componenter, public GGE_module
{
	public:
		Agenter();
		~Agenter() = default;
		/**
		 * create an agent and return its id
		 */
		size_t create_agent(
				shared_ptr<Tile> tile,
				shared_ptr<Sprite> sprite
				);

		bool move_agent(size_t agent, shared_ptr<Tile> tile);
		void navigate(size_t agent, shared_ptr<Tile> tile);
		void remove_agent(size_t agent);
		
		void tick() override;

	private:
		shared_ptr<Agent> get_agent(int);
};
