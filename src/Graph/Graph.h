//
// Created by migue on 11/05/2021.
//

#ifndef WASTE_APP_GRAPH_H
#define WASTE_APP_GRAPH_H

#include <vector>
#include <stack>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

template <class T> class Vertex{
    T info;
    vector<Edge<T>> outgoingEdges;
    void addEdge(Vertex<T> *dest, double weight);
    bool removeEdgeTo(Vertex<T> *dest);
public:
    Vertex(T info);
    friend class Graph<T>;

};

template <class T> class Edge {
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *dest, double weight);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T> class Graph {
    std::vector<Vertex<T> *> vertexSet;    // vertex set

    Vertex<T> *findVertex(const T &info) const;

public:
    int getNumVertex() const;

    bool addVertex(const T &info);

    bool removeVertex(const T &info);

    bool addEdge(const T &source, const T &dest, double weight);

    bool removeEdge(const T &source, const T &dest);

    vector<vector<int>> tarjan(const int id_src);

    void strongconnect(Vertex<T>* src, int &index, stack<Vertex<T>*> &st, vector<vector<int>> &scc)
};
#endif //WASTE_APP_GRAPH_H
