#include"GraphAlgo.h"

//
//-- Funckje wypisuj¹ce w konsoli --
//


void showMatrix(int** matrix, const unsigned int verticesNum)
{
    std::cout << std::endl;
    for (unsigned int row = 0; row < verticesNum; row++)
    {
        for (unsigned int column = 0; column < verticesNum; column++)
            std::cout << matrix[row][column] << ' ';
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void showAdjacencyList(const AdjacencyList* graph, const unsigned int verticesNum)
{
    std::cout << std::endl;
    for (unsigned int vertex = 0; vertex < verticesNum; vertex++)
    {
        std::cout << " -- " << vertex << " -- " << std::endl;
        for (auto adj : graph[vertex])
            std::cout << "-> Vertex: " << adj._vertex << " | Edge cost: " << adj._cost << std::endl;
    }
    std::cout << std::endl;
}


void showEdgeList(EdgeList& edges)
{
    for (auto e = edges.begin(); e != edges.end(); e++)
        std::cout << "Begin: " << e->_beg << " | End: " << e->_end << " | Cost: " << e->_cost << std::endl;
}

void showResultF(const PathF* result, const int size)
{
    std::cout << std::endl;
    for (int i = 0; i < size; i++)
        std::cout << i << " | Prev vertex: " << result[i]._prevVertex << " | Cost: " << result[i]._cost << std::endl;
    std::cout << std::endl;
}

//
//-- Funkcje tworz¹ce/wype³niaj¹ce struktry --
//

// ->Macierz s¹siedztwa

unsigned int readMatrix(int**& matrix, const std::string& fileName)
{
    if (matrix != nullptr) return 0;
    std::ifstream file;
    file.open(fileName.c_str());
    if (!file.good())
    {
        std::cout << "Matrix has not been loaded" << std::endl;
        return 0;
    }

    unsigned int vertexNum = 0;
    file >> vertexNum;

    matrix = new int* [vertexNum];
    for (int i = 0; i < vertexNum; i++)
        matrix[i] = new int[vertexNum];

    for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j < vertexNum; j++)
            file >> matrix[i][j];

    return vertexNum;
}

// ->Lista s¹siedztwa

void makeAdjacencyList(int** matrix, const unsigned int vertexNum, AdjacencyList*& dest)
{
    if (dest != nullptr) return;
    dest = new AdjacencyList[vertexNum];

    for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j < vertexNum; j++)
            if (matrix[i][j] != 0)
                dest[i].push_back(Adjacency(j, matrix[i][j]));
}

// ->Lista krawêdzi

void makeEdgeList(int** matrix, const unsigned int vertexNum, EdgeList& edges)
{
    if (matrix == nullptr) return;
    for (unsigned int row = 0; row < vertexNum; row++)
        for (unsigned int column = 0; column < vertexNum; column++)
            if (matrix[row][column] != 0 && !isEdgeValid(edges, column, row, matrix[row][column]))
                edges.emplace_back(Edge(row, column, matrix[row][column]));
}


bool isEdgeValid(EdgeList& edges, const int beg, const int end, const int cost)
{
    for (auto edge = edges.begin(); edge != edges.end(); edge++)
        if (edge->_beg == beg && edge->_end == end && edge->_cost == cost)
            return true;
    return false;
}

// ->PathF

void resetResultF(PathF*& result, const unsigned int vertexNum)
{
    if (result == nullptr)
    {
        result = new PathF[vertexNum];
        return;
    }

    for (int i = 0; i < vertexNum; i++)
    {
        result[i]._cost = PathF::DEFAULT_COST;
        result[i]._prevVertex = PathF::DEFAULT_PREV;
    }
}


//
//-- Algorytmy grafowe --
//

// ->Przeszukiwanie, szukanie po³¹czenia

bool isConnection(int** matrix, const int matrixSize, const unsigned int vertexA, const unsigned int vertexB)
{
    if (matrix == nullptr || matrixSize == 0) return false;

    bool isConnected = false;

    unsigned int* colorArray = new unsigned int[matrixSize];
    for (int i = 0; i < matrixSize; i++)
        colorArray[i] = 0;

    std::queue<int> que;
    que.push(vertexA);

    int vertex;

    while (que.empty() == false && !isConnected)
    {
        vertex = que.front();
        que.pop();
        colorArray[vertex] = 2;

        for (int i = 0; i < matrixSize; i++)
        {
            if (i == vertexB && matrix[vertex][i] != 0)
            {
                isConnected = true;
                break;
            }
            if (matrix[vertex][i] != 0 && colorArray[i] == 0)
            {
                colorArray[i] = 1;
                que.push(i);
            }
        }
    }
    delete[] colorArray;
    return isConnected;
}



// ->Algorytm Bellmana-Forda

bool BellmanFord(EdgeList& edges, const unsigned int vertexNum, const int start, PathF*& result)
{
    if (edges.empty() || vertexNum == 0) return false;

    resetResultF(result, vertexNum);

    result[start]._cost = 0;

    bool changed = false;
    for (int n = 0; n < vertexNum - 1; n++)
    {
        changed = false;
        for (auto edge = edges.begin(); edge != edges.end(); edge++)
            if (result[edge->_end]._cost > result[edge->_beg]._cost + edge->_cost)
            {
                result[edge->_end]._prevVertex = edge->_beg;
                result[edge->_end]._cost = result[edge->_beg]._cost + edge->_cost;
                changed = true;
            }
        if (changed == false) break;
    }

    if (isNegativeCycle(edges, result))
    {
        resetResultF(result, vertexNum);
        return false;
    }

    return true;
}

bool isNegativeCycle(EdgeList& edges, PathF* result)
{
    for (auto edge = edges.begin(); edge != edges.end(); edge++)
        if (result[edge->_end]._cost > result[edge->_beg]._cost + edge->_cost)
            return true;
    return false;
}


// ->Algorytm Dijkstry

/* Algorytm Dijkstry */
void Dijkstra(AdjacencyList* graph, const unsigned int vertexNum, const int startVertex, PathF*& result)
{
    if (graph == nullptr || vertexNum == 0) return;

    resetResultF(result, vertexNum);

    result[startVertex]._cost = 0;

    std::list<int> toVisit;
    for (int i = 0; i < vertexNum; i++)
        toVisit.push_back(i);

    std::list<int>::iterator vertex;
    while (toVisit.empty() == false)
    {
        vertex = std::move(smallestCost(toVisit.begin(), toVisit.end(), result));
        for (auto adj = graph[(*vertex)].begin(); adj != graph[(*vertex)].end(); adj++)
            if (result[adj->_vertex]._cost > result[*vertex]._cost + adj->_cost)
            {
                result[adj->_vertex]._prevVertex = *vertex;
                result[adj->_vertex]._cost = result[*vertex]._cost + adj->_cost;
            }
        toVisit.erase(vertex);
    }
}

std::list<int>::iterator smallestCost(const std::list<int>::iterator& beg, const std::list<int>::iterator& end, const PathF* p)
{
    std::list<int>::iterator result = beg;
    for (std::list<int>::iterator v = beg; v != end; v++)
        if (p[*v]._cost < p[*result]._cost)
            result = v;
    return result;
}

// ->Algorytm Kruskala

void Kruskal(EdgeList& graph, const unsigned int vertexNum, EdgeList& MST)
{
    if (graph.empty() || vertexNum == 0) return;
    if (MST.empty() == false) return;

    sortEdgeList(graph);

    int* trees = new int[vertexNum];
    int* color = new int[vertexNum];

    int newTreeNum = 0;

    fillArray(color, vertexNum, (int)WHITE);

    for (EdgeList::iterator current = graph.begin(); current != graph.end(); current++)
    {
        if (color[current->_beg] == WHITE && color[current->_end] == WHITE)
        {
            trees[current->_beg] = newTreeNum;
            trees[current->_end] = newTreeNum;
            color[current->_beg] = GREY;
            color[current->_end] = GREY;

            MST.push_back(*current);
            newTreeNum++;
            continue;
        }
        if (color[current->_beg] == WHITE)
        {
            trees[current->_beg] = trees[current->_end];
            color[current->_beg] = GREY;
            MST.push_back(* current);
            continue;
        }
        if (color[current->_end] == WHITE)
        {
            trees[current->_end] = trees[current->_beg];
            color[current->_end] = GREY;
            MST.push_back(*current);
            continue;
        }
        if (trees[current->_beg] != trees[current->_end])
        {
            mergeTrees(trees, vertexNum, trees[current->_beg], trees[current->_end], newTreeNum);
            MST.push_back(*current);
            newTreeNum++;
        }

    }

    delete[] trees;
    delete[] color;
}

void sortEdgeList(EdgeList& graph)
{
    EdgeList tmp;
    for (auto edge : graph)
        tmp.insert(std::lower_bound(tmp.begin(), tmp.end(), edge), edge);
    graph.clear();
    graph = std::move(tmp);
}

void mergeTrees(int* trees, const unsigned int size, const int treeA, const int treeB, const int newTree)
{
    for (unsigned int i = 0; i < size; i++)
        if (trees[i] == treeA || trees[i] == treeB)
            trees[i] = newTree;
}


// ->Algorytm Prima


void Prim(AdjacencyList* graph, const unsigned int verticesNum, PathF*& MST)
{
    if (graph == nullptr || verticesNum == 0) return;

    resetResultF(MST, verticesNum);

    std::list<int> toVisit;
    int* color = new int[verticesNum];

    fillArray(color, verticesNum, (int)WHITE);

    MST[0]._prevVertex = -1;
    MST[0]._cost = 0;
    toVisit.push_back(0);

    std::list<int>::iterator vertex;
    while (toVisit.empty() == false)
    {
        vertex = smallestCost(toVisit.begin(), toVisit.end(), MST);
      
        color[*vertex] = BLACK;

        for (auto adj : graph[*vertex])
        {
            if (color[adj._vertex] == WHITE)
            {
                toVisit.push_back(adj._vertex);
                color[adj._vertex] = GREY;

                MST[adj._vertex]._prevVertex = *vertex;
                MST[adj._vertex]._cost = adj._cost;
            }
            else if (color[adj._vertex] == GREY && MST[adj._vertex]._cost > adj._cost)
            {
                MST[adj._vertex]._prevVertex = *vertex;
                MST[adj._vertex]._cost = adj._cost;
            }
        }
        toVisit.erase(vertex);
    }

    delete[] color;
}
