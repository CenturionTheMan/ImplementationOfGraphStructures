#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

struct Vec3
{
    int vertexFrom;
    int vertexTo;
    int weight;

    Vec3* next;

    Vec3()
    {

    }

    Vec3(int vertexFrom, int vertexTo, int weight)
    {
        this->vertexFrom = vertexFrom;
        this->vertexTo = vertexTo;
        this->weight = weight;
        this->next = NULL;
    }
};

class EdgeList
{
private:
    Vec3* list;
    int vertexAmount;

public:
    EdgeList(int vertexAmount);
    ~EdgeList();
};

EdgeList::EdgeList(int vertexAmount)
{
    if(vertexAmount <= 0) 
        throw std::runtime_error("Vertex amount must be greater than 0");

    EdgeList::vertexAmount = 0;
    EdgeList::list = NULL;
}

EdgeList::~EdgeList()
{
}


