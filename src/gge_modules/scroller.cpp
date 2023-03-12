#include "scroller.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include "grider.hpp"
#include "../sdl_helper.hpp"
using namespace std;

Scroller::Scroller(int w, int h, SDL_Rect* max_scroll ):
	GGE_module(SCROLLER), _mid_screen({w/2, h/2})
{
	_scrolled.x = 0;
	_scrolled.y = 0;
	_max_scroll = max_scroll;
}

Scroller::~Scroller()
{
	delete _max_scroll;
}

bool Scroller::scroll(SDL_Point p)
{
#ifdef DEBUG
#include <iostream>
	cout << _scrolled << " -> ";
#endif

	int x_delta = p.x - _mid_screen.x;
	int y_delta = p.y - _mid_screen.y;



	_scrolled.x = (x_delta);// % 60;
	_scrolled.y = (y_delta) ;//% 60;
	_have_scrolled = true;

	// TODO max scroll
#ifdef DEBUG
	cout << _scrolled << endl;
#endif
	return true;
}

void Scroller::scroll_grid(shared_ptr<Grider> grid)
{
	if(not _have_scrolled)
		return;

	for (auto tile : grid->get_grid())
	{
		for(SDL_Point& corner : tile->get_corners())
		{
			corner.x += _scrolled.x;
			corner.y += _scrolled.y;
		}
	}

	_have_scrolled = false;
}
