#include "timer.hpp"
#include <cmath>
#include "componenter.hpp"

bool Timer::has_time_left(const shared_ptr<const Base_component> c) const
{
	auto d = std::chrono::duration_cast<ms_duration>(now() - c->creation).count();
	return d < c->milliseconds;
}

int Timer::time_left(const moment& creation_time, int lifetime_ms)
{
	auto d = std::chrono::duration_cast<ms_duration>(now() - creation_time).count();
	return lifetime_ms - d;
}
