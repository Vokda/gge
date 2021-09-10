#include "texter.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "sdl_helper.hpp"
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif 

Texter::Texter(SDL_Renderer* renderer)
{
	_renderer = renderer;
	_sdl_helper.check_null("SDL_TTF initalization", TTF_Init());
	_font = TTF_OpenFont(_font_name.c_str(), _font_size);
	string s = "Loading font ";
	s += _font_name;
	_sdl_helper.check_null(s, _font);
	_start_time = _timer.get_time_point();
}

Texter::~Texter()
{
	TTF_CloseFont(_font);
	for(auto& text: _texts)
	{
		SDL_DestroyTexture(text.texture);
	}
}

size_t Texter::create_text(
		const std::string& msg, 
		const SDL_Color& color, 
		const SDL_Rect& size,
		int ms
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

	text.milliseconds = ms;
	text.creation = _timer.get_time_point();
	SDL_Surface* text_surface = TTF_RenderText_Solid(
			_font, 
			msg.c_str(), 
			color
			);
	_sdl_helper.check_null("Texter: TTF_RenderTextSolid", text_surface);
	text.texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
	SDL_FreeSurface(text_surface);

	_texts.push_back(text);

#ifdef DEBUG
	cout << "Debug: Adv text created @ " << text.position.x << " " << text.position.y << endl;
	cout << "Debug: size " << rect.w << " " << rect.h << endl;
#endif 
	return _texts.size() - 1;
}

size_t Texter::create_text(const std::string& msg, SDL_Point position)
{
	Text text;
	text.permanent = true;
	text.position = position;
	SDL_Surface* text_surface = TTF_RenderText_Solid(
			_font, 
			msg.c_str(), 
			{255, 255, 255, 255}
			);
	_sdl_helper.check_null("Texter: TTF_RenderTextSolid", text_surface);
	text.texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
	text.size = {10,10,get_text_width(msg),_font_size*2};
	SDL_FreeSurface(text_surface);

	_texts.push_back(text);

#ifdef DEBUG
	cout << "Debug: Basic text created @ " << position.x << " " << position.y << endl;
#endif 
	return _texts.size() - 1;
}

void Texter::render_texts()
{
	for(auto& text: _texts)
	{
		SDL_RenderCopy(_renderer, text.texture, NULL, &text.size);
	}
}

void Texter::tick()
{
	for(auto itr = _texts.begin(); itr != _texts.end(); ++itr)
	{
		Text& text = (*itr);
		if(not text.permanent)
		{
			int time_left = _timer.time_left(text.creation, text.milliseconds);
			if(time_left <= 0)
			{
				_texts.erase(itr);
				break;
			}
		}
	}
	render_texts();
}

int Texter::get_text_width(const string& msg)
{
	return _font_size * msg.size();
}
