#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iomanip>
#include "Graph.h"

struct Connection
{
    Connection* nextConnection;
    int vertex;
    int weight;

    Connection() : nextConnection(nullptr), vertex(0), weight(0) {}

    Connection(int vertex, int weight)
        : nextConnection(nullptr), vertex(vertex), weight(weight) {}
};


class AdjacencyList : public Graph
{
private:
    Connection** arr;
    Connection* FindConnection(int fromVertex, int toVertex);

public:
    AdjacencyList(int vertexAmount);
    ~AdjacencyList();
    bool SetConnection(int fromVertex, int toVertex, int weight, bool isTwoSided);
    int GetWeight(int fromVertex, int toVertex);
    std::string ToString();
};
