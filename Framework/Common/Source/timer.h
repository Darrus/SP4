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

 public:
     StopWatch() ;
     ~StopWatch();
     void startTimer();
     double GetDeltaTime(); // get time in seconds since the last call to this function
     void waitUntil(long long time);  // wait until this time in milliseconds has passed
 };


#endif // _TIMER_H