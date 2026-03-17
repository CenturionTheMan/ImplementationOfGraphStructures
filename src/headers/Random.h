#pragma once
#include <random>

class Random
{
private:
    static std::mt19937& Engine()
    {
        static std::mt19937 engine(std::random_device{}());
        return engine;
    }

public:
    static int NextInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(Engine());
    }
};