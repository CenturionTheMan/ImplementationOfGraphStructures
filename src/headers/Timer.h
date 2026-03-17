#pragma once
#include <chrono>

class Timer
{
private:
    std::chrono::steady_clock::time_point start;

public:
    void Start()
    {
        start = std::chrono::steady_clock::now();
    }

    long long ElapsedNanoseconds()
    {
        auto end = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }

    double ElapsedMilliseconds()
    {
        return ElapsedNanoseconds() / 1'000'000.0;
    }
};