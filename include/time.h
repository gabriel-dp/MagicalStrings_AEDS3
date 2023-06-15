#ifndef TIME_H
#define TIME_H

typedef long double Time;

Time getRealTime();
void printElapsedTime(Time start, Time end);

#endif