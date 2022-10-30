
#include <iostream>
#include<string>
#include<fstream>
#include<queue>
#include<list>

#include"GraphAlgo.h"
#include"GraphStructures.h"


int main()
{
    const std::string fileName("macierz.txt");

    int** matrix = nullptr;
    unsigned int verticesNum = readMatrix(matrix, fileName);
    showMatrix(matrix, verticesNum);

    EdgeList edges;
    makeEdgeList(matrix, verticesNum, edges);
    showEdgeList(edges);

    AdjacencyList* graph = nullptr;
    makeAdjacencyList(matrix, verticesNum, graph);
    showAdjacencyList(graph, verticesNum);

    std::cout << "BELLMAN FORD\n";

    PathF* result = nullptr;
    std::cout<< "IS NEGATIVE CYCLE? " << BellmanFord(edges, verticesNum, 0, result) << std::endl;
    showResultF(result, verticesNum);

    std::cout << "DIJKSTRA\n";
    Dijkstra(graph, verticesNum, 0, result);
    showResultF(result, verticesNum);
    
    std::cout << "PRIM\n";
    Prim(graph, verticesNum, result);
    showResultF(result, verticesNum);

    std::cout << "KRUSKAL\n";
    EdgeList MST;
    Kruskal(edges, verticesNum, MST);
    showEdgeList(MST);

    if (result != nullptr)
        delete result;
    delete2Darray(matrix, verticesNum);

    return 0;
}
