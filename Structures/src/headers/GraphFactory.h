#pragma once

#include <memory>
#include <unordered_set>
#include <algorithm>

#include "Graph.h"
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include "EdgeList.h"
#include "Random.h"


enum class GraphType
{
    Matrix,
    List,
    Edge
};

inline std::unique_ptr<Graph> CreateGraph(GraphType type, int vertexAmount)
{
    switch(type)
    {
        case GraphType::Matrix:
            return std::make_unique<AdjacencyMatrix>(vertexAmount);
        case GraphType::List:
            return std::make_unique<AdjacencyList>(vertexAmount);
        case GraphType::Edge:
            return std::make_unique<EdgeList>(vertexAmount);
        default:
            throw std::runtime_error("Unknown graph type");
    }
}

inline void FillDirectedGraphWithLoopsRandomly(Graph& graph, float density, int minWeight = 1, int maxWeight = 1000)
{
    int n = graph.GetVertexAmount();
    int maxEdges = n * n;

    int targetEdges = std::max(1, static_cast<int>(density * maxEdges));

    std::unordered_set<long long> used;
    used.reserve(targetEdges);

    while ((int)used.size() < targetEdges)
    {
        int from = Random::NextInt(0, n - 1);
        int to = Random::NextInt(0, n - 1);

        long long key = (long long)from * n + to;

        if (used.insert(key).second)
        {
            int weight = Random::NextInt(minWeight, maxWeight);
            graph.SetConnection(from, to, weight, false);
        }
    }
}