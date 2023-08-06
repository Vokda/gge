#pragma once
#include <memory>
#include <SDL2/SDL.h>
#include "componenter.hpp"
#include "gge_module.hpp"
#include "../sdl_helper.hpp"
using namespace std;

class Graphics;

struct Sprite: public Base_component
{
	SDL_Point position; // mid point
	SDL_Rect size;
	SDL_Texture* texture;
	int view_port;
	void set_position(const SDL_Point& p)
	{
		position.x = p.x;
		position.y = p.y;
		size.x = p.x - size.w / 2;
		size.y = p.y - size.h / 2;
	}
};

class Graphics;

class Spriter: public Componenter, public GGE_module
{
	public:
		Spriter(shared_ptr<Graphics> g);
		~Spriter() = default;

		size_t create_sprite(
				int texture,
				const SDL_Point& p,
				int milliseconds
				);
		
		void change_texture(shared_ptr<Sprite>, int texture);
		void move_sprite(int texture, const SDL_Point& p);

		const list<component>& get_sprites() const { return get_components(); }

		shared_ptr<Sprite> get_sprite(size_t i) { return static_pointer_cast<Sprite>(get_component(i)); }
	private:
		shared_ptr<Graphics> _graphics;
		SDL_helper _sdl_helper;
};

