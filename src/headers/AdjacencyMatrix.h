#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

class AdjacencyMatrix
{
private:
    int** matrix;
    int vertexAmount;
public:
    
    AdjacencyMatrix(int vertexAmount);
    ~AdjacencyMatrix();
    bool SetConnection(int vertexFrom, int vertexTo, int weight, bool isTwoSided);
    int GetWeight(int fromVertex, int toVertex);
    std::string ToString();
};

