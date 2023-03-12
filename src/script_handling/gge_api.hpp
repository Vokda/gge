#ifndef GGE_API_HPP
#define GGE_API_HPP
#include "../sdl_helper.hpp"

#include "../gge_modules/gge_module_initializer.hpp"
#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include <queue>
#include "../gge_modules/registered_gge_modules.hpp"
#include "../core.hpp"


struct SDL_Point;
class Script_engine;
class Tile;

using namespace std;

class GGE_API
{
	public:
		GGE_API(Core& core);

		void set_script_engine(shared_ptr<Script_engine> se) { _script_engine = se; }

		SDL_KeyCode get_sdl_keycodes() const;

		void hello();

		// module init returns ID of module
		int init_graphics(const string& s, size_t, size_t);
		int init_events();
		int init_grider(int grid_type, int w, int h, int tile_size);
		int init_game_loop();
		int init_texter();
		int init_spriter();

		// events
		const std::queue<int>& get_events() const;
		int pop_event();
		// mouse ctrls
		std::vector<int> get_mouse_position();
		bool scroll(vector<int>& mouse_position);

		// core command
		void quit();

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


		// grid related 
		// create grid TODO paramaterize more
		int create_grid(size_t, size_t, int);
		// return index to tile in grid vector
		size_t get_tile_from_mouse(int x, int y);
		void set_tile_color(const vector<int>& c, size_t i);

		void set_tile_custom_data(size_t index, const string& name, void* data);
		void* get_tile_custom_data(size_t index, const string& name);

		// number
		/*void set_hex_data_number(const string& name, double data, size_t index);
		double get_hex_data_number(const string& name, size_t index);

		// text
		void set_hex_data_text(const string& name, const string& text, size_t index);
		const string& get_hex_data_text( size_t index, const string& name);*/

		// TODO if possible depending on loaded modules
		void add_command(rgm module, int command, rgm arg);
		int get_module(const string& module);

		void create_shape(int shape, const vector<int>& p);

		// load and image from path
		size_t load_image(const string& s);
		size_t create_sprite(size_t texture, int x, int y);

	private:
		Core& _core;
		shared_ptr<Script_engine> _script_engine = nullptr;
		SDL_helper _sdl_helper;
		GGE_module_initializer _gge_init;

		/*
		 * change the mouse input position based on the amount scrolled
		 */
 		void scroll_mouse(int& x, int& y);

		int add_module(rgm m, shared_ptr<GGE_module> ptr);

		shared_ptr<Tile> get_tile(size_t i);
#ifdef DEBUG
		int _x, _y = 0;
#endif
};

#endif
