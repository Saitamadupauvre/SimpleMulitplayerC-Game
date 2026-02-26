#pragma once

#include <chrono>

constexpr float FIXED_FRAMERATE = 60.0;

class Clock
{
public:
    Clock();

    void tick();
    double frameTime() const { return _frameTime; }
    double fixedDelta() const { return _fixed; }

private:
    using ClockType = std::chrono::high_resolution_clock;
    ClockType::time_point _previous;

    double _frameTime = 0.0;
    const double _fixed = 1.0 / FIXED_FRAMERATE;
};
