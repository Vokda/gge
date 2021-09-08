#ifndef TEXTER_HPP
#define TEXTER_HPP
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "sdl_helper.hpp"
#include "timer.hpp"
using namespace std;

struct Text
{
	bool permanent;
	moment creation;
	SDL_Point position;
	SDL_Rect size;
	SDL_Texture* texture;
	int milliseconds;
};

class Texter
{
	public:
		Texter(SDL_Renderer* renderer);
		~Texter();

		// will create text with white text
		size_t create_text(const std::string& msg, SDL_Point position);

		size_t create_text(
				const std::string& msg, 
				const SDL_Color&, 
				const SDL_Rect& size,
				int milliseconds);

		Text& operator[](size_t i);

		void tick();

	private:
		void remove_text();
		void render_texts();

		int get_text_width(const string&);

		std::vector<Text> _texts;
		string _font_name = "../fonts/courier_new.ttf";
		int _font_size = 24;
		TTF_Font* _font;
		SDL_Renderer* _renderer; // destruction handled by graphics.hpp
		SDL_helper _sdl_helper;
		Timer _timer;
		moment _start_time; // of the object;
};
#endif
