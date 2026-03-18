#include "AdjacencyMatrix.h"


#pragma region CTOR/DTOR

AdjacencyMatrix::AdjacencyMatrix(int vertexAmount) : Graph(vertexAmount)
{
    AdjacencyMatrix::matrix = new int*[vertexAmount];

    for(int i = 0; i < vertexAmount; i++)
    {
        AdjacencyMatrix::matrix[i] = new int[vertexAmount];
        for(int j = 0; j < vertexAmount; j++)
            AdjacencyMatrix::matrix[i][j] = 0;
    }

}

AdjacencyMatrix::~AdjacencyMatrix()
{
    if(AdjacencyMatrix::vertexAmount > 0)
    {
        for (int i = 0; i < AdjacencyMatrix::vertexAmount; i++)
        {
            delete[] AdjacencyMatrix::matrix[i];
        }
        delete[] AdjacencyMatrix::matrix;
    }
    AdjacencyMatrix::vertexAmount = 0;
}

#pragma endregion CTOR/DTOR


#pragma region PUBLIC

size_t AdjacencyMatrix::GetMemoryUsageBytes() const
{
    size_t total = sizeof(*this);
    total += sizeof(int*) * vertexAmount;
    total += sizeof(int) * vertexAmount * vertexAmount;
    return total;
}

bool AdjacencyMatrix::SetConnection(int fromVertex, int toVertex, int weight, bool isTwoSided)
{
    if(!this->IsInBounds(fromVertex, toVertex)) return false;

    AdjacencyMatrix::matrix[fromVertex][toVertex] = weight;

    if(isTwoSided)
    {
        AdjacencyMatrix::matrix[toVertex][fromVertex] = weight;
    }

    return true;
}

int AdjacencyMatrix::GetWeight(int fromVertex, int toVertex)
{
    if(!this->IsInBounds(fromVertex, toVertex))
    {
        throw std::out_of_range("One or both vertexes are out of range!");
    }
    return AdjacencyMatrix::matrix[fromVertex][toVertex];
}

std::string AdjacencyMatrix::ToString()
{
    std::ostringstream oss;
    int colWidth = 6;

    oss << std::setw(colWidth) << " ";
    for (int i = 0; i < vertexAmount; i++)
        oss << std::setw(colWidth) << i;
    oss << "\n";

    oss << std::string(colWidth * (vertexAmount + 1), '-') << "\n";

    for (int i = 0; i < vertexAmount; i++)
    {
        oss << std::setw(colWidth - 1) << i << "|";
        for (int j = 0; j < vertexAmount; j++)
        {
            oss << std::setw(colWidth) << matrix[i][j];
        }
        oss << "\n";
    }

    return oss.str();
}

#pragma endregion PUBLIC
