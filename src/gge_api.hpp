#ifndef GGE_API_HPP
#define GGE_API_HPP

#include <string>
#include <SDL2/SDL.h>
#include <vector>

class Core;

using namespace std;


class GGE_API
{
	public:
		GGE_API(Core& core);

		const string hello();

		SDL_KeyCode get_sdl_keycodes() const;

		// text
		size_t create_text(const string& text, int x, int y);
		size_t create_text(
				const string& text, 
				vector<int> color,
				vector<int> size,
				int milliseconds
				);

		//void add_text(const string& text, int ms);

		// mouse ctrls

	private:
		Core& _core;
};

#endif
