//
// Created by Georgios Zervos on 17/11/21.
//
#include <allegro5/allegro.h>
#include "../Include/timing.h"

SystemClock SystemClock::instance;

uint64_t SystemClock::milli_secs () const {
    return std::chrono::duration_cast<std::chrono::milliseconds>
            (clock.now().time_since_epoch()).count();
}

uint64_t SystemClock::micro_secs () const {
    return std::chrono::duration_cast<std::chrono::microseconds>
            (clock.now().time_since_epoch()).count();
}

uint64_t SystemClock::nano_secs() const {
    return std::chrono::duration_cast<std::chrono::nanoseconds>
            (clock.now().time_since_epoch()).count();
}

uint64_t GetSystemTime () {
    return SystemClock::Get().milli_secs();
}