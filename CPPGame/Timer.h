#pragma once
#include <functional>

class Timer
{
    bool clear = false;

public:
    void SetTimeout(std::function<void(void)>, int delay);
    void SetInterval(std::function<void(void)>, int interval);
    void Stop();
};

