#include <iostream>
#include "headers/AdjacencyMatrix.h"
#include "headers/AdjacencyList.h"
#include "headers/EdgeList.h"

int main()
{
    AdjacencyMatrix g1 = AdjacencyMatrix(5);
    g1.SetConnection(1,3,4,true);
    g1.SetConnection(4,4,1,false);
    g1.SetConnection(4,2,1,true);

    std::cout << "MACIERZ SASIEDZTWA\n";
    std::cout << g1.ToString();

    AdjacencyList g2 = AdjacencyList(5);
    g2.SetConnection(1,3,4,true);
    g2.SetConnection(4,4,1,false);
    g2.SetConnection(4,2,1,true);

    std::cout << std::endl;

    std::cout << "LISTA SASIADOW\n";
    std::cout << g2.ToString();

    std::cout << std::endl;

    EdgeList g3 = EdgeList(5);
    g3.SetConnection(1,3,4,true);
    g3.SetConnection(4,4,1,false);
    g3.SetConnection(4,2,1,true);
    std::cout << "LISTA KRAWEDZI\n";
    std::cout << g3.ToString();
}