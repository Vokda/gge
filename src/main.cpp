#include "scripter.hpp"
#include <iostream>
#include "core.hpp"
#include "initializer.hpp"
using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "Please provide a game file (.chai)" << endl;
		exit(1);
	}

	// init 
	Core core;
	Initializer initializer(core);
	Scripter scripter(argv[1], initializer);
	// looper (for main game loop)
	// graphics
	// event handler


	// 
}
