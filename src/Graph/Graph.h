//
// Created by migue on 11/05/2021.
//

#ifndef WASTE_APP_GRAPH_H
#define WASTE_APP_GRAPH_H

#include <vector>
#include <string>
#include <fstream>
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
    double x;
    double y;
    vector<Edge> outgoingEdges;
    void addEdge(Vertex *dest, double weight);
    bool removeEdgeTo(Vertex *dest);
    // Tarjan
    int index = -1;
    int low = -1;
    //Dijkstra
    int queueIndex;
    // required by MutablePriorityQueue
    double distance;
public:
    int getQueueIndex() const;

    void setQueueIndex(int queueIndex);
    double getDistance() const;

    void setDistance(double distance);

    int getIndex() const;

    void setIndex(int index);

    int getLow() const;

    void setLow(int low);
    Vertex(int ID, double x, double y);
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
    double weight;
public:
    Edge(Vertex *dest, double weight);
    Vertex * getDest();
    double getWeight() const;
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

    bool addVertex(int id,double x, double y);

    bool removeVertex(double x, double y);

    double distanceBetweenCoords(double x1, double x2, double y1, double y2);

    bool removeVertex(int id);

    bool addEdge(double sourceX, double sourceY, double destX, double destY);

    bool addEdge(int id1, int id2);

    bool removeEdge(double sourceX, double sourceY, double destX, double destY);

    Vertex *findVertex(int ID);

    vector<int> largestSCCKosaraju();

    vector<vector<int>> kosaraju();

    void DFS_Kosaraju(Vertex* src, stack<Vertex*> &L,  unordered_set<Vertex*> S);

    void assign(Vertex * u, Vertex * root, vector<int> &sc);

    Graph getTransposedGraph() const;

    Vertex *findClosestVertex(double x, double y);

    double pathCost(stack<Vertex *> path);


};



#endif //WASTE_APP_GRAPH_H