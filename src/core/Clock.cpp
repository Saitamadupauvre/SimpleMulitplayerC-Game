#include "./Clock.hpp"

Clock::Clock()
{
    _previous = ClockType::now();
}

void Clock::tick()
{
    auto now = ClockType::now();
    std::chrono::duration<double> elapsed = now - _previous;
    _frameTime = elapsed.count();

    if (_frameTime > 0.25)
        _frameTime = 0.25;

    _previous = now;
}
