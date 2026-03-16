#include <iostream>
#include "GraphFactory.h"

int main()
{
    auto g1 = CreateGraph(GraphType::Matrix, 5);
    g1->SetConnection(1,3,4,true);
    g1->SetConnection(4,4,1,false);
    g1->SetConnection(4,2,1,true);

    std::cout << "MACIERZ SASIEDZTWA\n";
    std::cout << g1->ToString();

    auto g2 = CreateGraph(GraphType::List, 5);
    g2->SetConnection(1,3,4,true);
    g2->SetConnection(4,4,1,false);
    g2->SetConnection(4,2,1,true);

    std::cout << "\nLISTA SASIADOW\n";
    std::cout << g2->ToString();

    auto g3 = CreateGraph(GraphType::Edge, 5);
    g3->SetConnection(1,3,4,true);
    g3->SetConnection(4,4,1,false);
    g3->SetConnection(4,2,1,true);

    std::cout << "\nLISTA KRAWEDZI\n";
    std::cout << g3->ToString();
}