#include "AdjacencyList.h"

#pragma region CTOR/DTOR

AdjacencyList::AdjacencyList(int vertexAmount) : Graph(vertexAmount)
{
    AdjacencyList::arr = new Connection*[AdjacencyList::vertexAmount];
    for (int i = 0; i < vertexAmount; i++)
        AdjacencyList::arr[i] = nullptr;
}

AdjacencyList::~AdjacencyList()
{
    for (int i = 0; i < AdjacencyList::vertexAmount; i++)
    {
        Connection* tmp = AdjacencyList::arr[i];
        while (tmp != nullptr)
        {
            Connection* toRemove = tmp;
            tmp = tmp->nextConnection;
            delete toRemove;
        }
    }
    if (AdjacencyList::arr != nullptr)
    {
        delete[] AdjacencyList::arr;
        AdjacencyList::arr = nullptr;
    }
}

#pragma endregion CTOR/DTOR


#pragma region PRIVATE

Connection* AdjacencyList::FindConnection(int fromVertex, int toVertex)
{
    if(!this->IsInBounds(fromVertex, toVertex)) return nullptr;

    Connection* next = AdjacencyList::arr[fromVertex];
    while (next != nullptr)
    {
        if (next->vertex == toVertex)
            return next;
        next = next->nextConnection;
    }
    return nullptr;
}

#pragma endregion PRIVATE 


#pragma region PUBLIC    

bool AdjacencyList::SetConnection(int fromVertex, int toVertex, int weight, bool isTwoSided)
{
    if(!this->IsInBounds(fromVertex, toVertex)) return false;

    Connection* con = AdjacencyList::FindConnection(fromVertex, toVertex);
    if (con != nullptr)
        con->weight = weight;
    else
    {
        Connection* newConnection = new Connection(toVertex, weight);
        newConnection->nextConnection = AdjacencyList::arr[fromVertex];
        AdjacencyList::arr[fromVertex] = newConnection;
    }

    return isTwoSided ? AdjacencyList::SetConnection(toVertex, fromVertex, weight, false) : true;
}

int AdjacencyList::GetWeight(int fromVertex, int toVertex)
{
    if(!this->IsInBounds(fromVertex, toVertex))
    {
        throw std::out_of_range("One or both vertexes are out of range!");
    }

    Connection* con = this->FindConnection(fromVertex, toVertex);
    return con == nullptr? 0 : con->weight;
}

std::string AdjacencyList::ToString()
{
    std::ostringstream oss;

    for (int i = 0; i < vertexAmount; i++)
    {
        oss << "[" << i << "] -> ";

        Connection* current = arr[i];
        while (current != nullptr)
        {
            oss << "(" << current->vertex << ", w=" << current->weight << ")";
            if (current->nextConnection != nullptr)
                oss << " -> ";
            current = current->nextConnection;
        }
        oss << "\n";
    }

    return oss.str();
}

#pragma endregion PUBLIC