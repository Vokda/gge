#ifndef GGE_API_HPP
#define GGE_API_HPP
#include "sdl_helper.hpp"

#include <string>
#include <SDL2/SDL.h>
#include <vector>

class Core;
class Chai_object;
struct SDL_Point;

using namespace std;


class GGE_API
{
	public:
		GGE_API(Core& core);

		const string hello();

		SDL_KeyCode get_sdl_keycodes() const;

		// no need to export
		void init_game_object(Chai_object& game_object); 

		/* gge_begin export */
		void init_graphics(const std::string&, size_t w, size_t h);
		void init_events();
		void init_grid(size_t width, size_t height, int tile_size);

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

		bool scroll(vector<int>& mouse_position);

		// hex related 
		// return index to hex in hex grid vector
		int get_hex_from_mouse(int x, int y);

		// TODO if possible depending on loaded modules
		void add_command(const string& command);

		/* gge_end export */

		void create_shape(int shape, const vector<int>& p);

		/*Chai_object& get_on_hex_data(int i);
		Chai_object& get_in_hex_data(int i);*/

	private:
		Core& _core;
		SDL_helper _sdl_helper;

		/*
		 * change the mouse input position based on the amount scrolled
		 */
 		void scroll_mouse(int& x, int& y);
};

#endif
