#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <memory>
struct Base_component;
using namespace std;
using namespace chrono;

using moment = time_point<system_clock>;

class Timer
{
	public:
		// TODO replace with now()
		moment get_time_point() const
		{
			return system_clock::now();
		};
		
		moment now() const
		{
			return system_clock::now();
		};
		
		bool has_time_left(const shared_ptr<const Base_component> c) const;

		int time_left(const moment& a, const moment& b);
		int time_left(const moment& m, int milliseconds);

	private:
		using ms_duration = std::chrono::milliseconds;
};

#endif 
