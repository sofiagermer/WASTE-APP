//
// Created by migue on 11/05/2021.
//

#ifndef WASTE_APP_GRAPH_H
#define WASTE_APP_GRAPH_H

#include <vector>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

template <class T> class Vertex{
    T info;
    double latitude;
    double longitude;
    vector<Edge<T>> outgoingEdges;
    void addEdge(Vertex<T> *dest, double weight);
    bool removeEdgeTo(Vertex<T> *dest);
public:
    Vertex(double lat, double lon,T info);
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

    Vertex<T> *findVertex(double lat, double lon);

public:
    int getNumVertex() const;

    bool addVertex(double lat, double lon,T &info);

    bool removeVertex(double latitude, double longitude);

    bool addEdge(double sourceLat, double sourceLon, double destLat, double destLon);

    bool removeEdge(double sourceLat, double sourceLon, double destLat, double destLon);

    double distanceBetweenCoords(double lat1, double lat2, double lon1, double lon2);

};
#endif //WASTE_APP_GRAPH_H
