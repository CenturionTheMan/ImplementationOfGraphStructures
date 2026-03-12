#include "AdjacencyMatrix.h"


#pragma region CTOR/DTOR

AdjacencyMatrix::AdjacencyMatrix(int vertexAmount)
{
    if(vertexAmount <= 0)
        throw std::runtime_error("Vertex amount must be greater than 0");

    AdjacencyMatrix::vertexAmount = vertexAmount;
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


bool AdjacencyMatrix::SetConnection(int vertexFrom, int vertexTo, int weight, bool isTwoSided)
{
    if(vertexFrom >= AdjacencyMatrix::vertexAmount || vertexTo >= AdjacencyMatrix::vertexAmount)
    {
        return false;
    }

    AdjacencyMatrix::matrix[vertexFrom][vertexTo] = weight;

    if(isTwoSided)
    {
        AdjacencyMatrix::matrix[vertexTo][vertexFrom] = weight;
    }

    return true;
}

int AdjacencyMatrix::GetWeight(int fromVertex, int toVertex)
{
    if(fromVertex >= AdjacencyMatrix::vertexAmount || toVertex >= AdjacencyMatrix::vertexAmount || toVertex <0 || fromVertex <0)
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
