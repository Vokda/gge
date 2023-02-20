#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
using namespace std;
using namespace chrono;

using moment = time_point<system_clock>;

class Timer
{
	public:
		moment get_time_point()
		{
			return system_clock::now();
		};

		int time_left(const moment& a, const moment& b);
		int time_left(const moment& m, int milliseconds);
};

#endif 
