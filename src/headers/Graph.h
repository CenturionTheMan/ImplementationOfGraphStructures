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
    
    virtual bool SetConnection(int fromVertex, int toVertex, int weight, bool isTwoSided) = 0;
    virtual int GetWeight(int fromVertex, int toVertex) = 0;
    virtual std::string ToString() = 0; 
};

