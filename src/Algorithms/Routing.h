//
// Created by miguel on 21/05/21.
//

#ifndef WASTE_APP_ROUTING_H
#define WASTE_APP_ROUTING_H


#include "../Graph/Graph.h"
#include "../Elements/Driver.h"

class Routing {
    static double heuristic(Vertex *start, Vertex *end);

    static stack<Vertex *> reconstructPath(map<Vertex *, Vertex *> cameFrom, Vertex *current,Vertex *start);

    static double distanceBetweenCoords(double x1, double x2, double y1, double y2);

public:
    static stack<Vertex *> dijkstra(Graph *graph,Vertex *start, Vertex *end);

    static stack<Vertex*> aStar(Graph *graph,Vertex *start, Vertex *end);

    static queue<Vertex *> nearestNeighbour(Graph *graph, Driver *driver,vector<Vertex*> pointsTravel);

    static double pathCost(stack<Vertex *> path);
};


#endif //WASTE_APP_ROUTING_H
