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
#include <map>
#include <queue>
#include <iostream>
#include <bits/stdc++.h>
#include "MutablePriorityQueue.h"

#define degreeToRadian (M_PI / 180.0)
#define INF std::numeric_limits<double>::max()

using namespace std;
class Edge;
class Graph;
class Vertex;

class Vertex{
    int ID;
    MapPoint *info;
    double x;
    double y;
    vector<Edge> outgoingEdges;
    void addEdge(Vertex *dest, double weight);
    bool removeEdgeTo(Vertex *dest);
    // Tarjan
    int index = -1;
    int low = -1;
    //Dijkstra
    int queueIndex = 0; // required by MutablePriorityQueue
    double distance;
public:
    Vertex(int ID, double x, double y, MapPoint *info);
    void updateInfo(MapPoint *info);
    double getX();
    double getY();
    bool operator<(Vertex* v);;
    vector<Edge> getOutgoingEdges();
    friend class Graph;
    friend class MutablePriorityQueue<Vertex*>;
    int getID();
};

class Edge {
    Vertex * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex *dest, double weight);
    Vertex * getDest();
    friend class Graph;
    friend class Vertex;
};

class Graph {
    vector<Vertex *> vertexSet;    // vertex set

    Vertex *findVertex(double x, double y);

public:
    Graph(string nodesFile,string edgesFile);
    Graph(){};
    vector<Vertex *> getVertexSet();

    int getNumVertex() const;

    bool addVertex(int id,double x, double y,MapPoint *info);

    bool removeVertex(double x, double y);

    bool removeVertex(int id);

    bool addEdge(double sourceX, double sourceY, double destX, double destY);

    bool addEdge(int id1, int id2);

    bool removeEdge(double sourceX, double sourceY, double destX, double destY);

    double distanceBetweenCoords(double x1, double x2, double y1, double y2);

    Vertex *findVertex(int ID);

    vector<vector<int>> tarjan(const int id_src);

    void strongconnect(Vertex* src, int &index, stack<Vertex*> &st, vector<vector<int>> &scc);

    stack<Vertex*> aStar(Vertex* start, Vertex* end);

    stack<Vertex*> dijkstra(Vertex* start,Vertex* end);

    double heuristic(Vertex* start, Vertex* end);

    stack<Vertex *> reconstructPath(map<Vertex *, Vertex *> cameFrom, Vertex *current,Vertex *start);

    queue<Vertex *> nearestNeighbour(double x,double y,vector<Vertex*> pointsTravel);
    vector<vector<int>> tarjan();

    void strongConnectedComponent(Vertex* src, vector<vector<int>> &scc); //Tarjan

    void DFS_Tarjan(Vertex* src, int nid, stack<Vertex*> &st, vector<vector<int>> &scc);

    vector<int> largestSCC();

    void preprocessGraph();

    vector<vector<int>> kosaraju();

    void DFS_Kosaraju(Vertex* src, stack<Vertex*> &L,  unordered_set<Vertex*> S);

    void assign(Vertex * u, Vertex * root, vector<int> &sc);

    Graph getTransposedGraph() const;

    Vertex *findClosestVertex(double x, double y);

    double pathCost(stack<Vertex *> path);


};

#endif //WASTE_APP_GRAPH_H