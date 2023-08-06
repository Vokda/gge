#include "spriter.hpp"
#include "graphics.hpp"

#include <sstream>
#include <iostream>
using namespace std;

Spriter::Spriter(shared_ptr<Graphics> g):
	GGE_module(SPRITER)
{
	_graphics = g;
}

size_t Spriter::create_sprite(int t, const SDL_Point& p, int ms)
{
	SDL_Texture* texture = _graphics->get_texture(t);
	if(texture == nullptr)
	{
		stringstream ss;
		ss <<"Spriter: texture not found: " << t << endl;
		throw runtime_error(ss.str());
	}
	Sprite sprite;
	sprite.texture = texture;
	sprite.permanent = (ms < 1 ? true : false);
	sprite.milliseconds = ms;

	SDL_Rect rect;
	rect.x = p.x;
	rect.y = p.y;
	int err = SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	_sdl_helper.check_null("SDL_QueryTexture", err);

	sprite.size = rect;
	sprite.set_position(p);

	_components.push_back(make_shared<Sprite>(sprite));
	cout << "Created sprite @ " << p << endl;
#ifdef DEBUG
	cout << "Sprite index: " << _components.size() - 1 << endl;
	cout << "sprites stored {" << endl;
	for(auto comp: _components)
	{
		cout << "\tsprite " <<comp << endl;
	}
	cout << '}' << endl;
#endif

	return _components.size() -1;
}

void Spriter::change_texture(shared_ptr<Sprite> sprite, int texture)
{
	auto* sdl_texture = _graphics->get_texture(texture);
	if(sdl_texture)
		sprite->texture = sdl_texture;
	else
		throw runtime_error("Not a valid texture index");
}
