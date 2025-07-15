#pragma once
#include <memory>
#include <map>
#include "gge_modules/registered_gge_modules.hpp"
#include "gge_modules/gge_module.hpp"
using namespace std;
#include "logger.hpp"

class Moduler
{
	public:
		Moduler();

		template<typename T>
			void set_module(rgm module,  shared_ptr<T> gge_module)
			{
                _log.info("Module %s", GGE_module::get_module_name(module).c_str());
				_modules[module] = gge_module;
			}

		shared_ptr<GGE_module> operator[](registered_gge_module m); 

		int list_modules() const;

	private:
		typedef map<registered_gge_module, shared_ptr<GGE_module>> modules_map;
		modules_map _modules;
        Logger::Log& _log;
};
