//
// Created by miguel on 21/05/21.
//

#include "Routing.h"

queue<Vertex *> Routing::nearestNeighbour(Graph graph,double x, double y, vector<Vertex *> pointsTravel) {
    queue<Vertex*> orderedCompletePath;
    Vertex *initialVertex = graph.findClosestVertex(x,y);
    orderedCompletePath.push(initialVertex);
    double minDistance;
    stack<Vertex*> next;
    vector<Vertex*>::iterator copy;
    while(!pointsTravel.empty()) {
        minDistance=INF;
        for (auto it = pointsTravel.begin(); it != pointsTravel.end(); it++) {
            auto path = aStar(graph,initialVertex, (*it));
            double aux = pathCost(path);
            if (aux < minDistance) {
                minDistance = aux;
                next = path;
                copy=it;
            }
        }
        while(!next.empty()){
            orderedCompletePath.push(next.top());
            next.pop();
        }
        pointsTravel.erase(copy);
        cout<<pointsTravel.size()<<endl;
    }
    return orderedCompletePath;
}

stack<Vertex *> Routing::reconstructPath(map<Vertex *, Vertex *> cameFrom, Vertex *current, Vertex *start) {
    stack<Vertex*> path;
    path.push(current);
    while(current!=start){
        current=cameFrom[current];
        path.push(current);
    }

    return path;
}

double Routing::heuristic(Vertex *start, Vertex *end) {
    return distanceBetweenCoords(start->getX(), end->getX(), start->getY(), end->getY());
}

stack<Vertex *> Routing::aStar(Graph graph,Vertex *start, Vertex *end) {
    map <Vertex*,Vertex*> cameFrom;
    for(auto v:graph.getVertexSet()){
        v->setDistance(INF);
        v->setQueueIndex(0);
    }
    start->setDistance(heuristic(start,end));
    MutablePriorityQueue<Vertex*> queue;
    queue.insert(start);
    Vertex* v;
    while(!queue.empty()){
        v=queue.extractMin();
        if(v==end) break;
        for(auto e:v->getOutgoingEdges()){
            double d=v->getDistance()- heuristic(v,end)+e.getWeight()+ heuristic(e.getDest(),end);
            if(d<e.getDest()->getDistance()){
                e.getDest()->setDistance(d);
                cameFrom[e.getDest()]=v;
                queue.insertOrDecreaseKey(e.getDest());
            }
        }
    }
    return reconstructPath(cameFrom,end,start);
}

stack<Vertex *> Routing::dijkstra(Graph graph,Vertex *start, Vertex *end) {
    map <Vertex*,Vertex*> cameFrom;
    for(auto v:graph.getVertexSet()){
        v->setDistance(INF);
        v->setQueueIndex(0);
    }
    start->setDistance(0);
    MutablePriorityQueue<Vertex*> queue;
    queue.insert(start);
    Vertex* v;
    while(!queue.empty()){
        v=queue.extractMin();
        if(v==end) break;
        for(auto e:v->getOutgoingEdges()){
            double d=v->getDistance()+e.getWeight();
            if(d<e.getDest()->getDistance()){
                e.getDest()->setDistance(d);
                cameFrom[e.getDest()]=v;
                queue.insertOrDecreaseKey(e.getDest());
            }
        }
    }
    return reconstructPath(cameFrom,end,start);

}

double Routing::pathCost(stack<Vertex *> path) {
    if(path.size()<2) return 0;
    double cost=0;
    auto v=path.top();
    path.pop();
    while(!path.empty()){
        for(auto e:v->getOutgoingEdges()){
            if(e.getDest()==path.top()){
                cost+=e.getWeight();
                break;
            }
        }
        v=path.top();
        path.pop();
    }
    return cost;
}

double Routing::distanceBetweenCoords(double x1, double x2, double y1, double y2) {
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}