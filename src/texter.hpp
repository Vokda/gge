#ifndef TEXTER_HPP
#define TEXTER_HPP
#include <regex>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "componenter.hpp"
#include "gge_module.hpp"
#include "sdl_helper.hpp"
class Graphics;
using namespace std;

struct Text: public Base_component
{
	SDL_Point position;
	SDL_Rect size;
	SDL_Texture* texture;
	int view_port;
	string text;
	SDL_Color color;
};

class Texter: public Componenter, public GGE_module
{
	public:
		// gge_begin export ctor
		Texter(shared_ptr<Graphics> g);
		// gge_end export ctor
		~Texter();

		size_t create_text(
				const std::string& msg, 
				const SDL_Color&, 
				const SDL_Rect& size,
				int milliseconds,
				int view_port);

		bool modify_text(size_t i, int value);

		const list<component>& get_texts() const { return get_components(); }

		int get_font_size() const { return _font_size; }
	private:
		regex _re;
		SDL_Texture* text_to_texture(const string& s, const SDL_Color& c);
		SDL_Renderer* _renderer;  // destruction handled by graphics.hpp

		int get_text_width(const string&);

		string _font_name = "../fonts/courier_new.ttf";
		int _font_size = 24;
		TTF_Font* _font;
		SDL_helper _sdl_helper;
};
#endif
