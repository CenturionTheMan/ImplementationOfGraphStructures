#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>
#include "Graph.h"

class AdjacencyMatrix : public Graph
{
private:
    int** matrix;
public:
    
    AdjacencyMatrix(int vertexAmount);
    ~AdjacencyMatrix();
    bool SetConnection(int fromVertex, int toVertex, int weight, bool isTwoSided);
    int GetWeight(int fromVertex, int toVertex);
    std::string ToString();
};

