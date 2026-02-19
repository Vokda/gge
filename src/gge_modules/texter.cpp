#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "texter.hpp"
#include "graphics.hpp"
#include <memory>

Texter::Texter(shared_ptr<Graphics> graphics):
	GGE_module(TEXTER)
{
	_renderer = graphics->get_renderer();
	check_null("SDL_TTF initalization", TTF_Init());
	_font = TTF_OpenFont(_font_name.c_str(), _font_size);
	string s = "Loading font ";
	s += _font_name;
	check_null(s, _font);
	_re = regex("%i"); // hard coded for now
}

Texter::~Texter()
{
	TTF_CloseFont(_font);
	for_each_component([&](component c)
	{
		auto text = static_pointer_cast<Text>(c);
		SDL_DestroyTexture(text->texture);
	});
}

bool Texter::modify_text(size_t i, int value)
{
	if(i >= get_number_of_components()) return false;
	auto text = static_pointer_cast<Text>(get_component_by_id(i));
	if(text == nullptr) return false;
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
	text.creation = now();
	text.text = msg;
	text.color = color;
	text.texture = text_to_texture(msg, color);

	auto component =(make_shared<Text>(text));

	_log.debug("Created text @ %i %i", text.position.x, text.position.y);
	_log.debug("size %i %i", rect.w, rect.h);
	_log.debug("text '%s'", msg.c_str());
	return component->id;
}

SDL_Texture* Texter::text_to_texture(const string& s, const SDL_Color& c)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(
			_font, 
			s.c_str(), 
			c
			);
	check_null("Texter: TTF_RenderTextSolid", text_surface);
	SDL_Texture* t = SDL_CreateTextureFromSurface(_renderer, text_surface);
	SDL_FreeSurface(text_surface);
	return t;
}

int Texter::get_text_width(const string& msg)
{
	return _font_size * msg.size();
}
