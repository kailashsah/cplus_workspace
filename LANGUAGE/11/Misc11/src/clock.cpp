#include <iostream>
using namespace std;
/*
	1. system_clock - Objects of class system_clock represent wall clock time from the system-wide realtime clock.
		
		steady_clock - Objects of class steady_clock represent clocks for which values of time_point never decrease as physical time advances and for which values of time_point advance at a steady rate relative to real time. That is, the clock may not be adjusted.


		high_resolution_clock - Objects of class high_resolution_clock represent clocks with the shortest tick period. high_resolution_clock may be a synonym for system_clock or steady_clock.
	
	2. For instance, the system wide clock might be affected by something like daylight savings time, at which point the actual time listed at some point in the future can actually be a time in the past. (E.g. in the US, in the fall time moves back one hour, so the same hour is experienced "twice") However, steady_clock is not allowed to be affected by such things.

	3. don't use high_resolution_clock, as it's an alias for one of these:

		system_clock: it's like a regular clock, use it for time/date related stuff
		steady_clock: it's like a stopwatch, use it for timing things.
*/

void run_clock()
{





}

//int main()
//{
//	return 0;
//}
