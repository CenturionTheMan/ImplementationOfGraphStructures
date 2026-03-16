#pragma once
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "Graph.h"

struct Edge
{
    int vertexFrom;
    int vertexTo;
    int weight;

    Edge* next;

    Edge(int vertexFrom, int vertexTo, int weight)
    {
        this->vertexFrom = vertexFrom;
        this->vertexTo = vertexTo;
        this->weight = weight;
        this->next = NULL;
    }

    Edge* AddNext(int vertexFrom, int vertexTo, int weight)
    {
        Edge* vec = new Edge(vertexFrom, vertexTo, weight);
        this->next = vec;
        return vec;
    }
};

class EdgeList : public Graph
{
private:
    Edge* head;
    Edge* tail;

    Edge* FindConnection(int from, int to);

public:
    EdgeList(int vertexAmount);
    ~EdgeList();
    bool SetConnection(int fromVertex, int toVertex, int weight, bool isTwoSided);
    int GetWeight(int fromVertex, int toVertex);
    std::string ToString();
};

