#pragma once

#include <libguile.h>
class Guile
{
	public:
		Guile();
		bool start_engine();
		void read_file(const char* c);
	private:
		void add_std_modules();
		SCM _scm;
};
