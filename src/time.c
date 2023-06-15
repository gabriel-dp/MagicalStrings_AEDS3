#include "../include/time.h"

#include <stdlib.h>
#include <sys/time.h>

// Returns real time in the moment that function is called
Time getRealTime() {
    // Get live time
    struct timeval now;
    gettimeofday(&now, NULL);

    // Join seconds and microseconds
    Time timeNow = now.tv_sec + ((Time)now.tv_usec / 1000000.0L);

    return timeNow;
}

// Prints the elapsed time of given start and end times
void printElapsedTime(Time start, Time end) {
    printf("Elapsed time = %Lf", end - start);
}