#include "timer.hpp"

int Timer::time_left(const moment& m, int ms)
{
	moment now = get_time_point();
	std::chrono::duration<double, std::milli>  d = now - m;
	return ms - d.count();
}
