#ifndef GGE_API_HPP
#define GGE_API_HPP

#include <string>
#include <SDL2/SDL.h>
#include <vector>

class Core;
class Chai_object;

using namespace std;


class GGE_API
{
	public:
		GGE_API(Core& core);

		const string hello();

		SDL_KeyCode get_sdl_keycodes() const;

		// text
		size_t create_text(const string& text, int view_port);
		size_t create_text(const string& text, int view_port, int ms, int x, int y);
		size_t create_text(
				const string& text, 
				vector<int> color,
				vector<int> size,
				int milliseconds,
				int view_port
				);

		bool modify_text(
				size_t index,
				int value
				);

		void set_hex_color(const vector<int>& c, size_t i);

		// mouse ctrls
		std::vector<int> get_mouse_position();
		const std::vector<int>& get_events() const;

		// hex related 
		// return index to hex in hex grid vector
		int get_hex_from_mouse(int x, int y);
		/*Chai_object& get_on_hex_data(int i);
		Chai_object& get_in_hex_data(int i);*/

	private:
		Core& _core;
};

#endif
