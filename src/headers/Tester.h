#pragma once

#include "GraphFactory.h"
#include "Timer.h"
#include "FileManager.h"
#include "Random.h"


inline double MeasureGetWeightMs(Timer& t, Graph& g)
{
    int from = Random::NextInt(0, g.GetVertexAmount()-1);
    int to = Random::NextInt(0, g.GetVertexAmount()-1);
    t.Start();
    g.GetWeight(from, to);
    return t.ElapsedMilliseconds();
}

inline double MeasureSetConnectionMs(Timer& t, Graph& g)
{
    int from = Random::NextInt(0, g.GetVertexAmount()-1);
    int to = Random::NextInt(0, g.GetVertexAmount()-1);
    int w = Random::NextInt(1, 1000);
    t.Start();
    g.SetConnection(from, to, w, false);
    return t.ElapsedMilliseconds();
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

inline void PerformTests(const std::string& outPath, int reps, std::vector<int> gSizes, std::vector<float> gDensities)
{
    Timer timer;
    FileManager fileManager;

    fileManager.Open(outPath);
    fileManager.Clear();

    GraphType gTypes[] = {GraphType::Edge, GraphType::List, GraphType::Matrix};

    
    std::vector<std::string> header = {"Rep", "Size", "Density", "GraphType", "CreationTime", "SizeInBytes", "GetWeightTimeMs", "SetConnectionTimeMs"};
    fileManager.AppendLineCSV(header);

    for (int r = 0; r < reps; r++)
    {
        for(int i = 0; i < gSizes.size(); i++)
        {
            int size = gSizes[i];
            for(int j = 0; j < gDensities.size(); j++)
            {
                float density = gDensities[j];
                
                for (int t = 0; t < 3; t++)
                {
                    GraphType gType = gTypes[t]; 
                    
                    timer.Start();
                    auto g = CreateGraph(gType, size);
                    double creationTime = timer.ElapsedMilliseconds();
                    
                    FillDirectedGraphWithLoopsRandomly(*g, density);

                    size_t sizeInBytes = g->GetMemoryUsageBytes();

                    double getWeightTimeMs = MeasureGetWeightMs(timer, *g);
                    double setConnectionTimeMs = MeasureSetConnectionMs(timer, *g);
                    
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

                    std::cout 
                        << "Rep: " << r
                        << " | Size: " << size
                        << " | Density: " << density
                        << " | Type: " << GraphTypeToString(gType)
                        << " | CreationTime: " << creationTime
                        << " | SizeInBytes: " << sizeInBytes
                        << " | GetWeight: " << getWeightTimeMs
                        << " | SetConnection: " << setConnectionTimeMs
                        << std::endl;
                }
            }
        }
    }

    fileManager.Close();
}

