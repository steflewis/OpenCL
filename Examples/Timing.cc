#include <Timing.h>

double wsecond() {
    struct timeval sampletime;
    double         time;

    gettimeofday( &sampletime, NULL );
    time = sampletime.tv_sec + (sampletime.tv_usec / 1000000.0);
    return( time*1000.0 ); // return time in ms
}
