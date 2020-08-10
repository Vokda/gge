#include "texter.hpp"

Texter::Texter(const SDL_Renderer& r):
	_renderer(r)
{
	_font = TTF_OpenFont("Sans.ttf", 24);
}

Texter::~Texter()
{
	TTF_CloseFont(_font);
}


