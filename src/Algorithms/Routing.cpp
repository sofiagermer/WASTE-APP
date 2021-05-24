//
// Created by miguel on 21/05/21.
//

#include "Routing.h"

queue<Vertex *> Routing::nearestNeighbour(Graph *graph,Driver *driver, vector<House *> housesToVisit) {
    queue<Vertex*> orderedCompletePath;
    Vertex *initialVertex = graph->findClosestVertex(driver->getX(),driver->getY());
    //Vertex *initialVertex = graph->findClosestVertex(200,300);
    orderedCompletePath.push(initialVertex);
    double minDistance;
    int initial=housesToVisit.size();
    stack<Vertex*> next;
    vector<House*>::iterator copy;
    int i=housesToVisit.size();
    bool flag=false;
    while(i!=0&&driver->getCar()->getCurrentCapacity()>0) {
        minDistance=INF;
        flag=true;
        for (auto it = housesToVisit.begin(); it != housesToVisit.end(); it++) {
            auto path = aStar(graph,orderedCompletePath.back(), (*it)->getHouseVertex());
            double aux = pathCost(path);
            if(aux<0){
                cout<<"caminho curto"<<endl;
                continue;
            }
            if (aux < minDistance && driver->getCar()->wouldFit((*it)->getAmountOfTrash()) ) {
                minDistance = aux;
                next = path;
                copy=it;
                flag=false;
            }
        }
        if(flag) break;
        cout<<"lixo em casa: "<<(*copy)->getAmountOfTrash()<<endl;
        cout<<"espaço livre: "<<driver->getCar()->getCurrentCapacity()<<endl;
        driver->getCar()->addTrash((*copy)->getAmountOfTrash());
        while(!next.empty()){
            orderedCompletePath.push(next.top());
            next.pop();
        }
        housesToVisit.erase(copy);
        i--;
    }
    return orderedCompletePath;
}

stack<Vertex *> Routing::reconstructPath(map<Vertex *, Vertex *> cameFrom, Vertex *current) {
    stack<Vertex*> path;
    path.push(current);
    while(current!= nullptr){
        current=cameFrom[current];
        if(current!= nullptr)
            path.push(current);
    }
    return path;
}

double Routing::heuristic(Vertex *start, Vertex *end) {
    return distanceBetweenCoords(start->getX(), end->getX(), start->getY(), end->getY());
}

stack<Vertex *> Routing::aStar(Graph *graph,Vertex *start, Vertex *end) {
    map <Vertex*,Vertex*> cameFrom;
    cameFrom[start]= nullptr;
    for(auto v:graph->getVertexSet()){
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
    return reconstructPath(cameFrom, end);
}

stack<Vertex *> Routing::dijkstra(Graph *graph,Vertex *start, Vertex *end) {
    map <Vertex*,Vertex*> cameFrom;
    cameFrom[start]= nullptr;
    for(auto v:graph->getVertexSet()){
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
    return reconstructPath(cameFrom, end);

}

double Routing::pathCost(stack<Vertex *> path) {
    if(path.size()<2) return -1;
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
