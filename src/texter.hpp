#pragma once
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


struct Text
{
	const std::string _txt;
	const SDL_Colour _colour;
};

class Texter
{
	public:
		Texter(const SDL_Renderer& renderer);
		~Texter();

		size_t create_text(const std::string& msg, const SDL_Color&);

		void render_texts();

	private:
		std::vector<Text> _texts;
		TTF_Font* _font;
		const SDL_Renderer& _renderer;

	friend class Graphics;
};
