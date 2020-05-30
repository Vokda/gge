#include "scripter.hpp"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "Please provide a game file (.chai)" << endl;
		exit(1);
	}
	Scripter scripter(argv[1]);
}
