#pragma once

#include <tuple>
#include <iomanip>
#include <sstream>

#include "GraphFactory.h"
#include "Timer.h"
#include "FileManager.h"
#include "Random.h"


inline double MeasureGetWeightMs(Timer& t, Graph& g, int singleOperationReps)
{
    int from = Random::NextInt(0, g.GetVertexAmount()-1);
    int to = Random::NextInt(0, g.GetVertexAmount()-1);
    t.Start();
    for (int i = 0; i < singleOperationReps; i++)
    {
        int w = g.GetWeight(from, to);
    }
    return t.ElapsedMilliseconds() / singleOperationReps;
}

inline double MeasureSetConnectionMs(Timer& t, Graph& g, int singleOperationReps)
{
    int from = Random::NextInt(0, g.GetVertexAmount()-1);
    int to = Random::NextInt(0, g.GetVertexAmount()-1);
    int w = Random::NextInt(1, 1000);
    t.Start();
    for (int i = 0; i < singleOperationReps; i++)
    {
        bool success = g.SetConnection(from, to, w, false);
    }
    return t.ElapsedMilliseconds() / singleOperationReps;
}

inline std::string GraphTypeToString(GraphType t)
{
    switch (t)
    {
        case GraphType::Edge: return "Edge";
        case GraphType::List: return "List";
        case GraphType::Matrix: return "Matrix";
        default: return "Unknown";
    }
}

struct TestCase
{
    int size;
    float density;
    GraphType type;
};

inline void PerformTests(const std::string& outPath, int reps, std::vector<int> gSizes, std::vector<float> gDensities, int singleOperationReps=100)
{
    //setup
    Timer timer;
    FileManager fileManager;

    fileManager.Open(outPath);
    fileManager.Clear();

    GraphType gTypes[] = {GraphType::Edge, GraphType::List, GraphType::Matrix};
    
    std::vector<std::string> header = {"Rep", "Size", "Density", "GraphType", "CreationTime", "SizeInBytes", "GetWeightTimeMs", "SetConnectionTimeMs"};
    fileManager.AppendLineCSV(header);

    //build test cases
    std::vector<TestCase> tests;
    for (int size : gSizes)
    {
        for (float density : gDensities)
        {
            for (GraphType type : {GraphType::Edge, GraphType::List, GraphType::Matrix})
            {
                tests.push_back({size, density, type});
            }
        }
    }
    Random::ShuffleVector(tests);

    //warmup
    for (int i = 0; i < singleOperationReps; i++)
    {
        auto g = CreateGraph(GraphType::Matrix, gSizes.back());
    }

    // run tests
    for (int r = 0; r < reps; r++)
    {
        Random::ShuffleVector(tests);
        for (int i = 0; i < tests.size(); i++)
        {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << i*100/(float)tests.size();
            std::cout << " [Progress]: " << oss.str() << "% of rep "<< r <<"\n";


            auto test = tests[i];
            int size = test.size;
            float density = test.density;
            GraphType gType = test.type; 

            std::cout << "  > Size: " << size
                << " | Density: " << density
                << " | Type: " << GraphTypeToString(gType) << std::endl;


            timer.Start();
            for (int k = 0; k < singleOperationReps; k++)
            {
                auto tmp1 = CreateGraph(gType, size);
            }
            double creationTime = timer.ElapsedMilliseconds() / singleOperationReps;
            std::cout << "  > Create: " << creationTime << " ms \n";

            auto g = CreateGraph(gType, size);
            FillDirectedGraphWithLoopsRandomly(*g, density);

            size_t sizeInBytes = g->GetMemoryUsageBytes();
            std::cout << "  > Memory: " << sizeInBytes << " bytes \n";

            double getWeightTimeMs = MeasureGetWeightMs(timer, *g, singleOperationReps);
            std::cout << "  > Find: " << getWeightTimeMs << " ms \n";

            double setConnectionTimeMs = MeasureSetConnectionMs(timer, *g, singleOperationReps);
            std::cout << "  > Add: " << setConnectionTimeMs << " ms \n\n";
            
            std::vector<std::string> row = {
                std::to_string(r),
                std::to_string(size),
                std::to_string(density),
                GraphTypeToString(gType),
                std::to_string(creationTime),
                std::to_string(sizeInBytes),
                std::to_string(getWeightTimeMs),
                std::to_string(setConnectionTimeMs)
            };
            fileManager.AppendLineCSV(row);
        }
    }
    fileManager.Close();
}

