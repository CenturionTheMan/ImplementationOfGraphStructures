#pragma once

#include <memory>
#include <vector>
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
    if(density < 0.01f)
        density = 0.01f;
    else if(density > 1.0f)
        density = 1.0f;

    int vertexAmt = graph.GetVertexAmount();
    int maxConnections = vertexAmt * vertexAmt;


    int targetEdges = std::max(1, static_cast<int>(density * maxConnections));

    std::vector<std::pair<int,int>> edges;
    edges.reserve(maxConnections);

    for (int i = 0; i < vertexAmt; i++)
    {
        for (int j = 0; j < vertexAmt; j++)
        {
            edges.emplace_back(i,j);   
        }
    }

    Random::ShuffleVector(edges);
    
    for (int i = 0; i < targetEdges; ++i)
    {
        int from = edges[i].first;
        int to = edges[i].second;
        int weight = Random::NextInt(minWeight, maxWeight);
        graph.SetConnection(from, to, weight, false);
    }
}