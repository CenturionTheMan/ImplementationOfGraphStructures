#include "Graph.h"


Graph::Graph(int vertexAmount): vertexAmount(vertexAmount)
{
    if (vertexAmount <= 0)
        throw std::runtime_error("Vertex amount must be greater than 0");
}

Graph::~Graph() = default;