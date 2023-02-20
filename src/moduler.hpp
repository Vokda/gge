#pragma once
#include <memory>
#include <map>
#include "gge_modules/registered_gge_modules.hpp"
class GGE_module;
using namespace std;

class Moduler
{
	public:
		Moduler();

		template<typename T>
			void set_module(rgm module,  shared_ptr<T> gge_module)
			{
				_modules[module] = gge_module;
			}

		shared_ptr<GGE_module> operator[](registered_gge_module m); 

		int list_modules() const;

	private:
		typedef map<registered_gge_module, shared_ptr<GGE_module>> modules_map;
		modules_map _modules;

};
