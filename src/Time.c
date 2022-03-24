#include "Time.h"

#ifdef __linux__
#include <sys/time.h>

u64 GetTime(){
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    return 1000000 * current_time.tv_sec + current_time.tv_usec;
}
#endif