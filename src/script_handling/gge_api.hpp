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
#include "../logger.hpp"

struct SDL_Point;
class Script_engine;
class Tile;
class Agent;

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
		int init_grider(int grid_type, int w, int h, int tile_size, int x, int y);
		int init_game_loop();
		int init_texter();
		int init_spriter();
		int init_agenter();
        int init_shaper();
        int init_gui();
        template<typename... Args>
            int initialize_gge_module(rgm module, Args&&... args)
            {
                auto ptr = initialize_module<module>(args...);
                return add_module(module, ptr);
            }
        template<typename... Args>
            int initialize_gge_module(int module, Args&&... args)
            {
                rgm m = rgm(module);
                return initialize_gge_module(m, args...);
            }
        template<typename T, typename... Args>
            shared_ptr<GGE_module> initialize_module(Args&&... args){
                _log.debug(typeid(T).name());
                return _gge_init.initialize<T>(args...);
            };

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
		int get_tile_from_mouse(int x, int y);
		void set_tile_color(const vector<int>& c, size_t i);
		const vector<int>& get_neighbors(int tile);

		void set_tile_custom_data(size_t index, const string& name, void* data);
		void* get_tile_custom_data(size_t index, const string& name);

		// text
		void set_hex_data_text(const string& name, const string& text, size_t index);
		const string& get_hex_data_text( size_t index, const string& name);

		// TODO if possible depending on loaded modules
		void add_command(rgm module, int command, rgm arg);
		int get_module(const string& module);

		// load and image from path
		size_t load_image(const string& s);
		size_t create_sprite(size_t texture, int x, int y);

		// agent related
		size_t create_agent(size_t texture, size_t tile);
		void move_agent(size_t agent, size_t to_tile);
		void remove_agent(size_t agent);
		vector<int> get_agents(int tile);
		void change_agent_sprite(int agent, int new_texture);

        // shape
        size_t create_shape(int shape_type, int pos_x, int pos_y, int size_x, int size_y, int ms);

        // GUI
        size_t create_button(const string& text, void* fn);


        void call_script_fn(void* fn); // always script function?

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
		shared_ptr<Agent> get_agent(size_t a);

        Logger::Log& _log;
#ifdef DEBUG
		int _x, _y = 0;
#endif
};

#endif
