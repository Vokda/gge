#pragma once

struct SDL_Window;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class Graphics
{
	public:
		Graphics(const std::string& window_name, size_t width, size_t height);
		~Graphics();

		void render();

	private:
		// some defaults
		int _screen_width = 640;
		int _screen_height = 400;

		SDL_Window* _window;
		SDL_Surface* _screen_surface;
		SDL_Renderer* _sdl_renderer;

		void check_null(const std::string& check_name, const void * SDL_struct);
		void check_null(const std::string& check_name, const int SDL_result);
};
