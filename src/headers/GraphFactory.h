#pragma once
#include <memory>
#include "Graph.h"
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include "EdgeList.h"

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