#pragma once

#include "texter.hpp"

struct SDL_Window;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;
class Hex_grid;
class SDL_helper;

class Graphics
{
	public:
		Graphics(const std::string& window_name, size_t width, size_t height, SDL_helper&);
		~Graphics();

		void load_image(const std::string& path);

		void clear_screen();
		void render();

		void draw_grid(const Hex_grid& grid);



	private:
		// some defaults
		int _screen_width = 640;
		int _screen_height = 400;

		//Texter _texter;
		SDL_Window* _window;
		SDL_Surface* _screen_surface;
		SDL_Renderer* _sdl_renderer;

		SDL_helper& _sdl_helper;
};
