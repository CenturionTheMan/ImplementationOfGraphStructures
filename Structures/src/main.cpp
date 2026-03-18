#include <iostream>
#include "GraphFactory.h"
#include "Tester.h"

void PrintDefault()
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

void GeneratePrintRandom()
{
    std::unique_ptr<Graph> g1 = CreateGraph(GraphType::Edge, 10);
    std::unique_ptr<Graph> g2 = CreateGraph(GraphType::List, 10);
    std::unique_ptr<Graph> g3 = CreateGraph(GraphType::Matrix, 10);

    FillDirectedGraphWithLoopsRandomly(*g1, 0.5);
    FillDirectedGraphWithLoopsRandomly(*g2, 0.5);
    FillDirectedGraphWithLoopsRandomly(*g3, 0.5);

    std::cout << "LISTA KRAWEDZI\n" << g1->ToString() << std::endl;
    std::cout << "LISTA SASIADOW\n" << g2->ToString() << std::endl;
    std::cout << "MACIERZ SASIADOW\n" << g3->ToString() << std::endl;
}

int main()
{
    // PrintDefault();
    // GeneratePrintRandom();

    std::string path = "test_results.csv";
    int reps = 50;
    std::vector<int> sizes = {100, 200, 300, 400, 500, 600, 700, 800};
    std::vector<float> densities = {0.25, 0.5, 0.75};

    PerformTests(path, reps, sizes, densities);
}

