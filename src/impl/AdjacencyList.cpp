#include <AdjacencyList.h>

#pragma region CTOR/DTOR

AdjacencyList::AdjacencyList(int vertexAmount)
{
    if(vertexAmount <= 0) 
        throw std::runtime_error("Vertex amount must be greater than 0");
    
        AdjacencyList::vertexAmount = vertexAmount;
    AdjacencyList::arr = new Connection*[AdjacencyList::vertexAmount];
    for (int i = 0; i < vertexAmount; i++)
    {
        AdjacencyList::arr[i] = NULL;
    }   
}

AdjacencyList::~AdjacencyList()
{
    for (int i = 0; i < AdjacencyList::vertexAmount; i++)
    {
        Connection* tmp = AdjacencyList::arr[i];
        while (tmp != NULL)
        {
            Connection* toRemove = tmp;
            tmp = tmp->nextConnection;
            delete toRemove;
        }
    }
    if(AdjacencyList::arr != NULL){
        delete AdjacencyList::arr;
        AdjacencyList::arr = NULL;
    }
}

#pragma endregion CTOR/DTOR


#pragma region PRIVATE

Connection* AdjacencyList::FindConnection(int fromVertex, int toVertex)
{
    if(fromVertex >= AdjacencyList::vertexAmount || toVertex >= AdjacencyList::vertexAmount  || fromVertex < 0 || toVertex < 0)
    {
        return NULL;
    }

    Connection* next = AdjacencyList::arr[fromVertex];
    while (next != NULL)
    {
        if(next->vertex == toVertex)
        {
            return next;
        }
        next = next->nextConnection;
    }
    return NULL;
}

#pragma endregion PRIVATE

#pragma endregion PUBLIC

bool AdjacencyList::SetConnection(int fromVertex, int toVertex, int weight, bool isTwoSided)
{
    if(fromVertex >= AdjacencyList::vertexAmount || toVertex >= AdjacencyList::vertexAmount  || fromVertex < 0 || toVertex < 0)
    {
        return false;
    }

    Connection* con = AdjacencyList::FindConnection(fromVertex, toVertex);
    if(con != NULL)
    {
        con->weight = weight;
    }
    else
    {
        Connection* newConnection = new Connection(toVertex, weight);
        newConnection->nextConnection = AdjacencyList::arr[fromVertex];
        AdjacencyList::arr[fromVertex] = newConnection;
    }

    return isTwoSided? AdjacencyList::SetConnection(toVertex, fromVertex, weight, false) : true;
}


std::string AdjacencyList::ToString()
{
    std::ostringstream oss;

    for (int i = 0; i < vertexAmount; i++)
    {
        oss << "[" << i << "] -> ";

        Connection* current = arr[i];
        while (current != NULL)
        {
            oss << "(" << current->vertex << ", w=" << current->weight << ")";
            if (current->nextConnection != NULL)
                oss << " -> ";
            current = current->nextConnection;
        }

        oss << "\n";
    }

    return oss.str();
}

#pragma endregion PUBLIC
