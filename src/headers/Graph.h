#pragma once
#include <string>
#include <stdexcept>

class Graph
{
protected:
    int vertexAmount;
    bool IsInBounds(int vertexFrom, int toVertex);

public:
    Graph(int vertexAmount);
    virtual ~Graph();
    
    int GetVertexAmount() { return vertexAmount; }
    virtual size_t GetMemoryUsageBytes() const = 0;
    virtual bool SetConnection(int fromVertex, int toVertex, int weight, bool isTwoSided) = 0;
    virtual int GetWeight(int fromVertex, int toVertex) = 0;
    virtual std::string ToString() = 0; 
};

