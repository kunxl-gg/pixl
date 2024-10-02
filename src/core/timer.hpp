#ifndef PIXL_TIMER_H
#define PIXL_TIMER_H

#include <chrono>
#include <string.h>
#include <time.h>

namespace pixl {

class Timer {
public:
    int getMillis();
    int delayMillis();

private:


};

}

#endif // !PIXL_TIMER_H
