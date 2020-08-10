#ifndef TEXTER_HPP
#define TEXTER_HPP
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <chrono>
using namespace std;
using namespace chrono;

struct Text
{
	std::string txt;
	SDL_Colour colour;
	bool permanent;
	time_point creation;
	SDL_Point position;
};

class Texter
{
	public:
		Texter(const SDL_Renderer& renderer);
		~Texter();

		size_t create_text(const std::string& msg, const SDL_Color&);
		Text& operator[](size_t i);

		void render_texts();

	private:
		std::vector<Text> _texts;
		TTF_Font* _font;
		const SDL_Renderer& _renderer;

	friend class Graphics;
};
#endif
