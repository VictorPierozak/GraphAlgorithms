#pragma once

#include"GraphStructures.h"
#include<iostream>
#include<string>
#include<fstream>
#include<queue>

// 
//-- Funkcje wypisuj�ce w konsoli --
//

/* Wypisuje macierz s�siedztwa */
void showMatrix(int** matrix, const unsigned int verticesNum);

/* Wypisuje list� s�siedztwa */
void showAdjacencyList(const AdjacencyList* graph, const unsigned int verticesNum);

/* Wypisuje list� kraw�dzi */
void showEdgeList(EdgeList& edges);

/* Wypisuje tablic� struktur PathF */
void showResultF(const PathF* result, const int size);


//
//-- Funkcje tworz�ce/wype�niaj�ce struktury --
//

// ->Macierz s�siedztwa

/* Czyta macierz s�siedztwa z pliku txt, pierwsza liczba w pliku to liczba wierzcho�k�w */
unsigned int readMatrix(int**& matrix, const std::string& fileName);

// ->Lista s�siedztwa

/* Tworzy list� s�siedztwa na podstawie macierzy s�siedztwa */
void makeAdjacencyList(int** matrix, const unsigned int vertexNum, AdjacencyList*& dest);

// ->Lista kraw�dzi

/* Tworzy list� kraw�dzi na podstawie macierzy s�siedztwa */
void makeEdgeList(int** matrix, const unsigned int vertexNum, EdgeList& edges);

/* Funkcja pomocnicza : sprawdza czy w li�cie kraw�dzi znajduje si� dana kraw�d� */
bool isEdgeValid(EdgeList& edges, const int beg, const int end, const int cost);

/* Inicjalizuje tablic� PathF o rozmiarze vertexNum
lub ustawia warto�ci w strukturze PathF na warto�ci domy�lne  */
void resetResultF(PathF*& result, const unsigned int vertexNum);

//
//-- Algorytmy grafowe --
//

// ->Przeszukiwanie, szukanie po��czenia

/*Sprawdza czy istnieje po��czenie mi�dzy dwoma wierzcho�kami*/
bool isConnection(int** matrix, const int matrixSize, const unsigned int vertexA, const unsigned int vertexB);

// ->Algorytm Bellmana-Forda

/* Algorytm Bellmana-Forda */
bool BellmanFord(EdgeList& edges, const unsigned int vertexNum, const int start, PathF*& result);

/* Funckja pomocnicza: sprawdza, czy istnieje ujemny cykl w grafie */
bool isNegativeCycle(EdgeList& edges, PathF* result);

// ->Algorytm Dijkstry

/* Algorytm Dijkstry */
void Dijkstra(AdjacencyList* graph, const unsigned int vertexNum, const int startVertex, PathF*& result);

/* Funkcja pomocnicza: wyszukuje w li�cie wierzcho�ek o najmiejszym koszcie doj�cia */
std::list<int>::iterator smallestCost(const std::list<int>::iterator& beg, const std::list<int>::iterator& end, const PathF* p);

// ->Algorytm Kruskala

/* Algorytm Kruskala */
void Kruskal(EdgeList& graph, const unsigned int vertexNum, EdgeList& MST);

void sortEdgeList(EdgeList& graph);

/* Funckja pomocnicza: ��czy dwa drzewa w algorytmie Kruskala */
void mergeTrees(int* trees, const unsigned int size, const int treeA, const int treeB, const int newTree);

// ->Algorytm Prima

void Prim(AdjacencyList* graph, const unsigned int verticesNum, PathF*& MST);

//
// -- Inne --
//

/*Usuwa tablic� dwuwymiarow�*/
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