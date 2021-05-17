//
// Created by migue on 11/05/2021.
//

#include "Graph.h"


#define degreeToRadian (M_PI / 180.0)

Vertex::Vertex(int id,double lat, double lon,MapPoint *i): info(i), latitude(lat), longitude(lon), ID(id){}


Edge::Edge(Vertex *d, double w): dest(d), weight(w) {}


int Graph::getNumVertex() const {
    return vertexSet.size();
}


Vertex * Graph::findVertex(double lat, double lon) {
    for (auto v : vertexSet)
        if (v->latitude == lat && v->longitude == lon)
            return v;
    return NULL;
}

bool Graph::addVertex(int id,double lat, double lon,MapPoint *in) {
    if(findVertex(lat,lon)!=NULL)
        return false;
    vertexSet.push_back(new Vertex(id,lat,lon,in));
    return true;
}

bool Graph::addEdge(double sourceLat, double sourceLon, double destLat, double destLon) {
    if(findVertex(sourceLat,sourceLon)==NULL||findVertex(destLat,destLon)==NULL)
        return false;
    auto v1= findVertex(sourceLat,sourceLon);
    double d=distanceBetweenCoords(sourceLat,destLat,sourceLon,destLon);
    v1->addEdge(findVertex(destLat,destLon), d);
    return true;
}

void Vertex::addEdge(Vertex *d, double w) {
    outgoingEdges.push_back(Edge(d,w));
}

bool Graph::removeEdge(double sourceLat, double sourceLon, double destLat, double destLon) {
    auto *v1=findVertex(sourceLat,sourceLon);
    auto *v2=findVertex(destLat,destLon);
    if(v1==NULL||v2==NULL) return false;
    return v1->removeEdgeTo(v2);
}

bool Vertex::removeEdgeTo(Vertex *d) {
    typename std::vector<Edge>::iterator it;
    for(it=outgoingEdges.begin();it!=outgoingEdges.end();it++){
        if(it->dest==d){
            outgoingEdges.erase(it);
            return true;
        }
    }
    return false;
}

double Vertex::getLatitude() {
    return latitude;
}

double Vertex::getLongitute() {
    return longitude;
}

void Vertex::updateInfo(MapPoint *i) {
    info=i;
}


bool Graph::removeVertex(double latitude, double longitude) {
    auto v=findVertex(latitude,longitude);
    if(v==NULL) return false;
    typename std::vector<Vertex*>::iterator it;
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

double Graph::distanceBetweenCoords(double lat1, double lat2, double long1, double long2) {
    //uses the Haversine formula to calculate distances in a sphere
    double dLong = (long2 - long1) * degreeToRadian;
    double dLat = (lat2 - lat1) * degreeToRadian;
    double a = pow(sin(dLat / 2.0), 2) + cos(lat1 * degreeToRadian) * cos(lat2 * degreeToRadian) * pow(sin(dLong / 2.0), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = 6371 * c; //6371 is the Earth's radius
    return d;
}

Vertex *Graph::findVertex(int ID) {
    for (auto v : vertexSet)
        if (v->ID == ID)
            return v;
    return NULL;
}


bool Graph::addEdge(int id1, int id2) {
    auto v1= findVertex(id1);
    auto v2= findVertex(id2);
    if(v1==NULL||v2==NULL)
        return false;
    double d=distanceBetweenCoords(v1->getLatitude(),v2->getLatitude(),v1->getLongitute(),v2->getLongitute());
    v1->addEdge(v2, d);
    return true;
}


Graph::Graph(string nodesFile, string edgesFile, string tagsFile) {
    ifstream nFile(nodesFile),eFile(edgesFile),tFile(tagsFile);


    int numberElements;
    char c;

    int id;
    double latitude,longitude;

    //Reads number of nodes
    nFile>>numberElements;
    std::cout<<(numberElements);
    for(int i=0;i<numberElements;i++){
        //Reads each vertex/node's info
        nFile>>c>>id>>c>>latitude>>c>>longitude>>c;
        addVertex(id,latitude,longitude, nullptr);

    }
    int v1,v2;

    eFile>>numberElements;

    for(int i=0;i<numberElements;i++){
        eFile>>c>>v1>>c>>v2>>c;
        addEdge(v1,v2);
    }

    string type;
    int tags;
    tFile>>tags;
    for(int i=0;i<tags;i++){
        tFile>>type;
        tFile>>numberElements;
        TrashType trashType;
        int maxCapacity;
        MapPoint *info;
        if(type=="Bin"){
            info=new TrashContainer(20,Regular);
        }
        else if(type=="Glass"){
            info=new TrashContainer(500,Glass);
        }
        else if(type=="Regular"){
            info=new TrashContainer(500,Regular);
        }
        else if(type=="Paper"){
            info=new TrashContainer(500,Paper);
        }
        else if(type=="Plastic"){
            info=new TrashContainer(500,Plastic);
        }
        else if(type=="Plastic"){
            info=new TrashContainer(500,Plastic);
        }
        else if(type=="Facility"){
            info=new GarbageCollectionFacility();
        }
        for(int i=0;i<numberElements;i++){
            tFile>>id;
            auto v=findVertex(id);
            v->updateInfo(info);
        }
    }

}

/*-----------------TARJAN----------------------------------------------------------------*/
/*
vector<vector<int>> Graph::tarjan(const int id_src) {
    for (Vertex<T>* vertex : vertexSet) {
        vertex->index = -1;
        vertex->low = -1;
        vertex->onStack = false;
    }

    vector<vector<int>> scc;

    int index = 0;
    stack<Vertex<T>*> st;

    for (Vertex<T>* vertex : vertexSet) {
        if (vertex->index == -1) {
            strongconnect(vertex, index, st, scc);
        }
    }

    return scc;
}

template<class T>
void Graph::strongconnect(Vertex* src, int &index, stack<Vertex*> &st, vector<vector<int>> &scc) {
    src->index = index;
    src->low = index;
    index++;
    st.push(src);
    src->onStack = true;

    for (Edge<T>* edge : src->getAdj()) {
        if (edge->dest->index == -1) {
            strongconnect(edge->dest, index, st, scc);
            src->low = min(src->low, edge->dest->low);
        } else if (edge->dest->onStack) {
            src->low = min(src->low, edge->dest->index);
        }
    }

    if (src->low == src->index) {
        vector<int> sc;
        Vertex<T>* w;
        do {
            w = st.top();
            st.pop();
            w->onStack = false;
            sc.push_back(w->getId());
        } while (w != src);
        scc.push_back(sc);
    }
}
 */
/*---------------------------------------------------------------------------------------*/

