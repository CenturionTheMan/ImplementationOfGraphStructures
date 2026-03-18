#pragma once
#include <random>
#include <vector>
#include <algorithm>

class Random
{
private:
    static std::mt19937& Engine()
    {
        static std::mt19937 engine(std::random_device{}());
        return engine;
    }

public:
    /// @brief Return random int within given (inclusive) bounds
    /// @param min 
    /// @param max 
    /// @return random int
    static int NextInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(Engine());
    }

    template<typename T>
    static void ShuffleVector(std::vector<T>& vector)
    {
        std::shuffle(vector.begin(), vector.end(), Engine());
    }
};