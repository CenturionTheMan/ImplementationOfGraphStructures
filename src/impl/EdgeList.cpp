#include "EdgeList.h"

EdgeList::EdgeList(int vertexAmount) : Graph(vertexAmount)
{
    if(vertexAmount <= 0) 
        throw std::runtime_error("Vertex amount must be greater than 0");

    EdgeList::vertexAmount = vertexAmount;
    EdgeList::head = nullptr;
    EdgeList::tail = nullptr;
}

EdgeList::~EdgeList()
{
    if(this->vertexAmount == 0) return;

    Edge* tmp = head;
    while (tmp != nullptr)
    {
        Edge* next = tmp->next;
        delete tmp;
        tmp = next;
    }
}

Edge* EdgeList::FindConnection(int from, int to)
{
    Edge* tmp = this->head;

    while (tmp != nullptr)
    {
        if(tmp->vertexFrom == from && tmp->vertexTo == to)
            return tmp;
        else
            tmp = tmp->next;
    }
    
    return nullptr;
}


bool EdgeList::SetConnection(int fromVertex, int toVertex, int weight, bool isTwoSided)
{
    if(fromVertex <0 || fromVertex >= this->vertexAmount || toVertex < 0 || toVertex >= this->vertexAmount)
        return false;

    Edge* toModify = this->FindConnection(fromVertex, toVertex);
    if(toModify != nullptr)
    {
        toModify->weight = weight;
        return isTwoSided? this->SetConnection(toVertex, fromVertex, weight, false) : true;
    }

    if(this->head == nullptr)
    {
        this->head = new Edge(fromVertex,toVertex,weight);
        this->tail = this->head;
        return isTwoSided? this->SetConnection(toVertex, fromVertex, weight, false) : true;
    }

    Edge* tmp = new Edge(fromVertex, toVertex, weight);
    this->tail->next = tmp;
    this->tail = this->tail->next;

    return isTwoSided? this->SetConnection(toVertex, fromVertex, weight, false) : true;
}

std::string EdgeList::ToString()
{
    std::ostringstream oss;

    Edge* current = this->head;
    while (current != nullptr)
    {
        oss << "(" << current->vertexFrom << " -> " << current->vertexTo << ", w=" << current->weight << ")\n";
        current = current->next;
    }

    if (this->head == nullptr)
        oss << "(empty)\n";

    return oss.str();
}