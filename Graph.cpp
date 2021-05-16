//
// Created by migue on 11/05/2021.
//

#include "Graph.h"
#include <math.h>

#define degreeToRadian (M_PI / 180.0)

template <class T>
Vertex<T>::Vertex(double lat, double lon,T i): info(i), latitude(lat),longitude(lon){}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
Vertex<T> * Graph<T>::findVertex(double lat, double lon) {
    for (auto v : vertexSet)
        if (v->latitude == lat && v->longitude == lon)
            return v;
    return NULL;
}

template <class T>
bool Graph<T>::addVertex(double lat, double lon,T &in) {
    if(findVertex(lat,lon)!=NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(lat,lon,in));
    return true;
}

template <class T>
bool Graph<T>::addEdge(double sourceLat, double sourceLon, double destLat, double destLon) {
    if(findVertex(sourceLat,sourceLon)==NULL||findVertex(destLat,destLon)==NULL)
        return false;
    auto v1= findVertex(sourceLat,sourceLon);
    double d=distanceBetweenCoords(sourceLat,destLat,sourceLon,destLon);
    v1->addEdge(findVertex(destLat,destLon), d);
    return true;
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    outgoingEdges.push_back(Edge<T>(d,w));
}

template <class T>
bool Graph<T>::removeEdge(double sourceLat, double sourceLon, double destLat, double destLon) {
    auto *v1=findVertex(sourceLat,sourceLon);
    auto *v2=findVertex(destLat,destLon);
    if(v1==NULL||v2==NULL) return false;
    return v1->removeEdgeTo(v2);
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    typename std::vector<Edge<T>>::iterator it;
    for(it=outgoingEdges.begin();it!=outgoingEdges.end();it++){
        if(it->dest==d){
            outgoingEdges.erase(it);
            return true;
        }
    }
    return false;
}

template <class T>
bool Graph<T>::removeVertex(double latitude, double longitude) {
    auto v=findVertex(latitude,longitude);
    if(v==NULL) return false;
    typename std::vector<Vertex<T>*>::iterator it;
    auto copy=vertexSet.begin();
    for(it=vertexSet.begin();it!=vertexSet.end();it++){
        if((*it)->latitude==latitude && (*it)->longitude==longitude){
            copy=it;
            continue;
        }
        (*it)->removeEdgeTo(v);
    }
    vertexSet.erase(copy);
    return true;
}

template<class T>
double Graph<T>::distanceBetweenCoords(double lat1, double lat2, double long1, double long2) {
    //uses the Haversine formula to calculate distances in a sphere
    double dLong = (long2 - long1) * degreeToRadian;
    double dLat = (lat2 - lat1) * degreeToRadian;
    double a = pow(sin(dLat / 2.0), 2) + cos(lat1 * degreeToRadian) * cos(lat2 * degreeToRadian) * pow(sin(dLong / 2.0), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = 6371 * c; //6371 is the Earth's radius
    return d;
}


