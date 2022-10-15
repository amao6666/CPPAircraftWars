#include "Timer.h"
#include <chrono>
#include <thread>

void Timer::SetTimeout(std::function<void(void)> function, int delay) {
    this->clear = false;
    std::thread t([=]() {
        if (this->clear) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if (this->clear) return;
        function();
        });
    t.detach();
}

void Timer::SetInterval(std::function<void(void)> function, int interval) {
    this->clear = false;
    std::thread t([=]() {
        while (true) {
            if (this->clear) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if (this->clear) return;
            function();
        }
        });
    t.detach();
}

void Timer::Stop() {
    this->clear = true;
}