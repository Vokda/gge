#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "texter.hpp"
#include "graphics.hpp"
#include <memory>
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif 

Texter::Texter(shared_ptr<Graphics> graphics):
	GGE_module(TEXTER)
{
	_renderer = graphics->get_renderer();
	_sdl_helper.check_null("SDL_TTF initalization", TTF_Init());
	_font = TTF_OpenFont(_font_name.c_str(), _font_size);
	string s = "Loading font ";
	s += _font_name;
	_sdl_helper.check_null(s, _font);
	_start_time = _timer.get_time_point();

	_re = regex("%i"); // hard coded for now
}

Texter::~Texter()
{
	TTF_CloseFont(_font);
	for(auto comp: _components)
	{
		auto text = static_pointer_cast<Text>(comp);
		SDL_DestroyTexture(text->texture);
	}
}

bool Texter::modify_text(size_t i, int value)
{
	if(i >= _components.size()) return false;
	auto itr = _components.begin();
	while(itr != _components.end())
	{
		itr++;
	}
	auto text = static_pointer_cast<Text>(*itr);
	string& s = text->text;
	string r = regex_replace(s, _re, to_string(value));
	if(s == r) return false;
	s = r;
	text->texture = text_to_texture(s, text->color);
	return true;
}

size_t Texter::create_text(
		const std::string& msg, 
		const SDL_Color& color, 
		const SDL_Rect& size,
		int ms,
		int vp
		)
{
	Text text;
	text.permanent = (ms < 1 ? true : false);

	SDL_Rect rect = size;
	text.position = {rect.x, rect.y};
	cout << "position " << size << endl;
	if(rect.w < 0)
		rect.w = get_text_width(msg);
	if(rect.h < 0)
		rect.h = _font_size * 2;
	text.size = rect;

	text.view_port = vp;
	text.milliseconds = ms;
	text.creation = _timer.get_time_point();
	text.text = msg;
	text.color = color;
	text.texture = text_to_texture(msg, color);

	_components.push_back(make_shared<Text>(text));

#ifdef DEBUG
	cout << "Debug: Adv text created @ " << text.position.x << " " << text.position.y << endl;
	cout << "Debug: size " << rect.w << " " << rect.h << endl;
	cout << "Debug: text '" << msg << "'" << endl;
#endif 
	return _components.size() - 1;
}

SDL_Texture* Texter::text_to_texture(const string& s, const SDL_Color& c)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(
			_font, 
			s.c_str(), 
			c
			);
	_sdl_helper.check_null("Texter: TTF_RenderTextSolid", text_surface);
	SDL_Texture* t = SDL_CreateTextureFromSurface(_renderer, text_surface);
	SDL_FreeSurface(text_surface);
	return t;
}

int Texter::get_text_width(const string& msg)
{
	return _font_size * msg.size();
}
