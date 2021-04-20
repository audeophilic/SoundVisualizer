#pragma once
#include <chrono>

//Simple timer class based on the one from EECS 281
class Timer {
    std::chrono::time_point<std::chrono::system_clock> cur;
    std::chrono::time_point<std::chrono::system_clock> pauseStart;
    std::chrono::duration<double> elap;
    std::chrono::duration<double> pauseElap;
public:
    Timer() :
        cur(),
        pauseStart(),
        elap(std::chrono::duration<double>::zero()),
        pauseElap(std::chrono::duration<double>::zero())
    {}
    void start() {
        cur = std::chrono::system_clock::now();
    }
    void stop() {
        elap += std::chrono::system_clock::now() - cur - pauseElap;
    }
    void pause() {
        pauseStart = std::chrono::system_clock::now();
    }
    void resume() {
        pauseElap += std::chrono::system_clock::now() - pauseStart;
    }
    double pauseduration() {
        return pauseElap.count();
    }
    double elapsed() {
        std::chrono::duration<double> elapsedtime = std::chrono::system_clock::now() - cur - pauseElap;
        return elapsedtime.count();
    }
    void reset() {
        elap = std::chrono::duration<double>::zero();
        pauseElap = std::chrono::duration<double>::zero();
    }
    double seconds() {
        return elap.count();
    }
};
