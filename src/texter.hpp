#ifndef TEXTER_HPP
#define TEXTER_HPP
#include <vector>
#include <string>
#include <memory>
#include <regex>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "sdl_helper.hpp"
#include "timer.hpp"
class Graphics;
using namespace std;

struct Text
{
	bool permanent;
	moment creation;
	SDL_Point position;
	SDL_Rect size;
	SDL_Texture* texture;
	int milliseconds;
	int view_port;
	string text;
	SDL_Color color;
};

class Texter
{
	public:
		Texter(shared_ptr<Graphics> g);
		~Texter();

		size_t create_text(
				const std::string& msg, 
				const SDL_Color&, 
				const SDL_Rect& size,
				int milliseconds,
				int view_port);

		bool modify_text(size_t i, int value);

		const vector<Text>& get_texts() const { return _texts; }
		Text& operator[](size_t i);

		void tick();

		int get_font_size() const { return _font_size; }

	private:
		void remove_text();
		regex _re;
		SDL_Texture* text_to_texture(const string& s, const SDL_Color& c);

		int get_text_width(const string&);



		std::vector<Text> _texts;
		string _font_name = "../fonts/courier_new.ttf";
		int _font_size = 24;
		TTF_Font* _font;
		SDL_Renderer* _renderer; // destruction handled by graphics.hpp
		shared_ptr<Graphics> _graphics;
		SDL_helper _sdl_helper;
		Timer _timer;
		moment _start_time; // of the object;
};
#endif
