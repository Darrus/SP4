#ifndef _TIMER_H
#define _TIMER_H

#include <windows.h>
#include "SingletonTemplate.h"

class StopWatch : public Singleton<StopWatch>
{ 
	friend Singleton<StopWatch>;
    LARGE_INTEGER frequency;
    LARGE_INTEGER prevTime, currTime;
    double LIToSecs( LARGE_INTEGER & L) ;
    UINT     wTimerRes;

	double dt;
 public:
     StopWatch() ;
     ~StopWatch();
     void startTimer();
     double GetElapsedTime(); // get time in seconds since the last call to this function
	 inline double GetDeltaTime() { return dt; }; // Get Delta Time
     void waitUntil(long long time);  // wait until this time in milliseconds has passed
 };


#endif // _TIMER_H