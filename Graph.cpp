//
// Created by migue on 11/05/2021.
//

#include "Graph.h"

template <class T>
Vertex<T>::Vertex(T i): info(i) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
    if(findVertex(in)!=NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

template <class T>
bool Graph<T>::addEdge(const T &source, const T &dest, double w) {
    if(findVertex(source)==NULL||findVertex(dest)==NULL)
        return false;
    auto v1= findVertex(source);
    v1->addEdge(findVertex(dest),w);
    return true;
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    outgoingEdges.push_back(Edge<T>(d,w));
}

template <class T>
bool Graph<T>::removeEdge(const T &source, const T &dest) {
    auto *v1=findVertex(source);
    auto *v2=findVertex(dest);
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
bool Graph<T>::removeVertex(const T &in) {
    auto v=findVertex(in);
    if(v==NULL) return false;
    typename std::vector<Vertex<T>*>::iterator it;
    auto copy=vertexSet.begin();
    for(it=vertexSet.begin();it!=vertexSet.end();it++){
        if((*it)->info==in){
            copy=it;
            continue;
        }
        (*it)->removeEdgeTo(v);
    }
    vertexSet.erase(copy);
    return true;
}


