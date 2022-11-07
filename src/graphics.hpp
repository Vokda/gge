#pragma once

#include "gge_module.hpp"
#include <memory>
#include <SDL2/SDL.h>
#include "sdl_helper.hpp"
using namespace std;

struct SDL_Window;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;
class Hex_grid;
class Texter;
class Scroller;
class Shape;

class Graphics: public GGE_module
{
	public:
		// gge_begin export ctor
		Graphics(const std::string& window_name, size_t width, size_t height);
		// gge_end export ctor
		~Graphics();

		enum viewport {MAIN, BAR, SIDE_BAR};

		void load_image(const std::string& path);

		// gge_begin make commands
		void clear_screen();
		void render();

		// always draws to _main_view
		void draw(const shared_ptr<GGE_module> grid);
		// gge_end make commands

		SDL_Renderer* get_renderer() { return _sdl_renderer; }
		int get_screen_width() { return _screen_width; }
		int get_screen_height() { return _screen_height; }

		const SDL_Rect& get_viewport(int vp);
		const SDL_Rect& get_viewport(viewport vp);

	private:
		void draw_grid(const shared_ptr<Hex_grid> grid);
		void draw_text(const shared_ptr<Texter>);
		// flushes renderer if viewport changes
		void set_viewport(viewport v);

		// some defaults
		int _screen_width = 640;
		int _screen_height = 400;

		SDL_Window* _window;
		SDL_Renderer* _sdl_renderer;

		// view ports
		// something akin to civ 2 interface
		SDL_Rect _main_view; // where game is drawn
		SDL_Rect _bar_view; // top info bar view
		SDL_Rect _side_bar_view; // side info bar view
		viewport _current_viewport = MAIN;

		SDL_helper _sdl_helper;
};
