#pragma once
#include <SDL2/SDL.h>
#include <memory>
using namespace std;
class Hex_grid;

class Scroller
{
	public:
		Scroller(
				int w,
				int h,
				SDL_Rect* max_scroll = nullptr);
		~Scroller();

		/*
		 * call when scrolling the window in anyway
		 * only for main viewport at the moment
		 */
		bool scroll(SDL_Point); 

		// actually move the grid
		void scroll_grid(shared_ptr<Hex_grid> grid);

		const SDL_Point& get_scrolled() const {return _scrolled;}
	private:

		SDL_Point _scrolled; // how far away we've scrolled
		const SDL_Point _mid_screen;
		SDL_Rect* _max_scroll; // null if no max
		bool _have_scrolled = false;
};
