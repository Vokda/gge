#pragma once
#include "gge_module.hpp"
class Script_engine;
class Core;

class GGE_module_initializer
{
	public:
		GGE_module_initializer() = default;

		/*template<typename T, typename... Args>
			shared_ptr<GGE_module> initialize(rgm module, Args... args);*/

		// ye olde C way
		// int rather than rgm to supress warnings regarding varargs
		//shared_ptr<GGE_module> initialize(int module...);

		/* for safe keeping
		shared_ptr<GGE_module> graphics(const string& s, size_t, size_t);
		shared_ptr<GGE_module> events();
		shared_ptr<GGE_module> grid(size_t, size_t, int);
		shared_ptr<GGE_module> game_loop();
		*/

		// gge_begin import ctor_decl
		shared_ptr<GGE_module> graphics(const string& s, size_t, size_t);
		shared_ptr<GGE_module> events();
		shared_ptr<GGE_module> grid(size_t, size_t, int);
		shared_ptr<GGE_module> game_loop(Script_engine&, Core&);
		// gge_end import ctor_decl
};
