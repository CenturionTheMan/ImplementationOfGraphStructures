#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

struct Connection
{
    Connection* nextConnection;
    int vertex;
    int weight;

    Connection()
    {

    }

    Connection(int vertex, int weight)
    {
        this->vertex = vertex;
        this->weight = weight;
        this->nextConnection = NULL;
    }
};


class AdjacencyList
{
private:
    Connection** arr;
    int vertexAmount;

    Connection* FindConnection(int fromVertex, int toVertex);

public:
    AdjacencyList(int vertexAmount);
    ~AdjacencyList();
    bool SetConnection(int fromVertex, int toVertex, int weight, bool isTwoSided);
    std::string ToString();
};
