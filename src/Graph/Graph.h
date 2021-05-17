//
// Created by migue on 11/05/2021.
//

#ifndef WASTE_APP_GRAPH_H
#define WASTE_APP_GRAPH_H

#include <vector>
#include <string>
#include <fstream>
#include "../Elements/TrashContainer.h"
#include "../Elements/GarbageCollectionFacility.h"
#include <stack>
#include <math.h>
#include <iostream>

using namespace std;
class Edge;
class Graph;
class Vertex;

class Vertex{
    int ID;
    MapPoint *info;
    double latitude;
    double longitude;
    vector<Edge> outgoingEdges;
    void addEdge(Vertex *dest, double weight);
    bool removeEdgeTo(Vertex *dest);
    double getLatitude();
    double getLongitute();
public:
    Vertex(int ID,double lat, double lon,MapPoint *info);
    void updateInfo(MapPoint *info);
    friend class Graph;
};

class Edge {
    Vertex * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex *dest, double weight);
    friend class Graph;
    friend class Vertex;
};

class Graph {
    std::vector<Vertex *> vertexSet;    // vertex set

    Vertex *findVertex(double lat, double lon);

public:
    Graph(string nodesFile,string edgesFile,string tagsFile);

    int getNumVertex() const;

    bool addVertex(int id,double lat, double lon,MapPoint *info);

    bool removeVertex(double latitude, double longitude);

    bool addEdge(double sourceLat, double sourceLon, double destLat, double destLon);

    bool addEdge(int id1, int id2);

    bool removeEdge(double sourceLat, double sourceLon, double destLat, double destLon);

    double distanceBetweenCoords(double lat1, double lat2, double lon1, double lon2);

    Vertex *findVertex(int ID);

    vector<vector<int>> tarjan(const int id_src);

    void strongconnect(Vertex* src, int &index, stack<Vertex*> &st, vector<vector<int>> &scc);
};
#endif //WASTE_APP_GRAPH_H
