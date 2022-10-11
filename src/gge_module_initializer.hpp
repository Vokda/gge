#pragma once
#include "moduler.hpp"
#include "gge_module.hpp"
#include <string>

class GGE_module_initializer
{
	public:
		GGE_module_initializer(Moduler& m);

		template<typename... Args>
			void init_module(rgm module, Args...)
			{
				switch(module)
				{
					//gge_begin set_modules
					case(GRAPHICS):
						_moduler.set_module(module, make_shared<Graphics>(Args...));
						break;
					//gge_end set_modules
				}
			}
	private:
		Moduler& _moduler;
};
