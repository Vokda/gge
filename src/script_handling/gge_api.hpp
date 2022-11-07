#ifndef GGE_API_HPP
#define GGE_API_HPP
#include "../sdl_helper.hpp"

#include "../gge_module_initializer.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include "../registered_gge_modules.hpp"
#include "../core.hpp"


struct SDL_Point;
class Script_engine;

using namespace std;

class GGE_API
{
	public:
		GGE_API(Core& core);

		void set_script_engine(shared_ptr<Script_engine> se) { _script_engine = se; }

		SDL_KeyCode get_sdl_keycodes() const;

		void hello();

		// module init
		void init_graphics(const string& s, size_t, size_t);
		void init_events();
		void init_grid(size_t, size_t, int);
		void init_game_loop();

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
		int get_module(const string& module);


		void create_shape(int shape, const vector<int>& p);

	private:
		Core& _core;
		shared_ptr<Script_engine> _script_engine = nullptr;
		SDL_helper _sdl_helper;
		GGE_module_initializer _gge_init;

		/*
		 * change the mouse input position based on the amount scrolled
		 */
 		void scroll_mouse(int& x, int& y);
		void add_module(rgm m, shared_ptr<GGE_module> ptr);
};

#endif
