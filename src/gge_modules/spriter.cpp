#include "spriter.hpp"
#include "graphics.hpp"

Spriter::Spriter(shared_ptr<Graphics> g):
	GGE_module(SPRITER)
{
	_graphics = g;
}

size_t Spriter::create_sprite(size_t t, const SDL_Point& p, int ms)
{
	SDL_Texture* texture = _graphics->get_texture(t);
	Sprite sprite;
	sprite.position = p;
	sprite.texture = texture;
	sprite.permanent = (ms < 1 ? true : false);
	sprite.milliseconds = ms;

	SDL_Rect rect;
	rect.x = p.x;
	rect.y = p.y;
	int err = SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	_sdl_helper.check_null("SDL_QueryTexture", err);

	sprite.size = rect;

	_components.push_back(make_shared<Sprite>(sprite));
	return _components.size() -1;
}
