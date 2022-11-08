//
// Created by Georgios Zervos on 17/11/21.
//

#ifndef CS454_SUPER_MARIO_GAME_TIMING_H
#define CS454_SUPER_MARIO_GAME_TIMING_H


#include <chrono>

class SystemClock final {
    private:
        std::chrono::high_resolution_clock clock;
        static SystemClock instance;
        SystemClock() = default;
    public:
        static auto Get() { return instance; }
        uint64_t milli_secs () const;
        uint64_t micro_secs () const;
        uint64_t nano_secs () const;
};

#endif //CS454_SUPER_MARIO_GAME_TIMING_H
