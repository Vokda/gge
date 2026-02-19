#include "timer.hpp"
#include <cmath>

int Timer::time_left(const moment& m, int ms)
{
	moment now = get_time_point();
	using ms_duration = std::chrono::milliseconds;
	auto d = std::chrono::duration_cast<ms_duration>(now - m).count();
	return std::max(ms - (int)d, 0);
}
