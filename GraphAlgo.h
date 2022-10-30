#pragma once

#include"GraphStructures.h"
#include<iostream>
#include<string>
#include<fstream>
#include<queue>

// 
//-- Funkcje wypisuj¹ce w konsoli --
//

/* Wypisuje macierz s¹siedztwa */
void showMatrix(int** matrix, const unsigned int verticesNum);

/* Wypisuje listê s¹siedztwa */
void showAdjacencyList(const AdjacencyList* graph, const unsigned int verticesNum);

/* Wypisuje listê krawêdzi */
void showEdgeList(EdgeList& edges);

/* Wypisuje tablicê struktur PathF */
void showResultF(const PathF* result, const int size);


//
//-- Funkcje tworz¹ce/wype³niaj¹ce struktury --
//

// ->Macierz s¹siedztwa

/* Czyta macierz s¹siedztwa z pliku txt, pierwsza liczba w pliku to liczba wierzcho³ków */
unsigned int readMatrix(int**& matrix, const std::string& fileName);

// ->Lista s¹siedztwa

/* Tworzy listê s¹siedztwa na podstawie macierzy s¹siedztwa */
void makeAdjacencyList(int** matrix, const unsigned int vertexNum, AdjacencyList*& dest);

// ->Lista krawêdzi

/* Tworzy listê krawêdzi na podstawie macierzy s¹siedztwa */
void makeEdgeList(int** matrix, const unsigned int vertexNum, EdgeList& edges);

/* Funkcja pomocnicza : sprawdza czy w liœcie krawêdzi znajduje siê dana krawêdŸ */
bool isEdgeValid(EdgeList& edges, const int beg, const int end, const int cost);

/* Inicjalizuje tablicê PathF o rozmiarze vertexNum
lub ustawia wartoœci w strukturze PathF na wartoœci domyœlne  */
void resetResultF(PathF*& result, const unsigned int vertexNum);

//
//-- Algorytmy grafowe --
//

// ->Przeszukiwanie, szukanie po³¹czenia

/*Sprawdza czy istnieje po³¹czenie miêdzy dwoma wierzcho³kami*/
bool isConnection(int** matrix, const int matrixSize, const unsigned int vertexA, const unsigned int vertexB);

// ->Algorytm Bellmana-Forda

/* Algorytm Bellmana-Forda */
bool BellmanFord(EdgeList& edges, const unsigned int vertexNum, const int start, PathF*& result);

/* Funckja pomocnicza: sprawdza, czy istnieje ujemny cykl w grafie */
bool isNegativeCycle(EdgeList& edges, PathF* result);

// ->Algorytm Dijkstry

/* Algorytm Dijkstry */
void Dijkstra(AdjacencyList* graph, const unsigned int vertexNum, const int startVertex, PathF*& result);

/* Funkcja pomocnicza: wyszukuje w liœcie wierzcho³ek o najmiejszym koszcie dojœcia */
std::list<int>::iterator smallestCost(const std::list<int>::iterator& beg, const std::list<int>::iterator& end, const PathF* p);

// ->Algorytm Kruskala

/* Algorytm Kruskala */
void Kruskal(EdgeList& graph, const unsigned int vertexNum, EdgeList& MST);

void sortEdgeList(EdgeList& graph);

/* Funckja pomocnicza: ³¹czy dwa drzewa w algorytmie Kruskala */
void mergeTrees(int* trees, const unsigned int size, const int treeA, const int treeB, const int newTree);

// ->Algorytm Prima

void Prim(AdjacencyList* graph, const unsigned int verticesNum, PathF*& MST);

//
// -- Inne --
//

/*Usuwa tablicê dwuwymiarow¹*/
template<typename T>
void delete2Darray(T** arr, const unsigned int size)
{
    for (int i = 0; i < size; i++)
        delete arr[i];
    delete arr;
}

template<typename T>
void fillArray(T* arr, const unsigned int size, const T value)
{
    for (int i = 0; i < size; i++)
        arr[i] = value;
}