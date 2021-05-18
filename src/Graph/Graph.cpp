#include "Graph.h"


#define degreeToRadian (M_PI / 180.0)
#define INF std::numeric_limits<double>::max()

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

int Vertex::getID(){
    return ID;
}

vector<Edge> Vertex::getOutgoingEdges() {
    return outgoingEdges;
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

    //return sqrt((lat2-lat1)*(lat2-lat1)+(long2-long1)*(long2-long1));
}

Vertex *Graph::findVertex(int ID) {
    for (auto v : vertexSet)
        if (v->ID == ID)
            return v;
    return NULL;
}

vector<Vertex *> Graph::getVertexSet() {
    return vertexSet;
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
    cout<< "==================================="<<endl;
    cout<< "         LOADING THE GRAPH         "<<endl;
    cout<< "==================================="<<endl;
    cout<<"0% ";
    ifstream nFile(nodesFile),eFile(edgesFile),tFile(tagsFile);

    int numberElements;
    char c;

    int id;
    double latitude,longitude;

    //Reads number of nodes
    nFile>>numberElements;
    for(int i=0;i<numberElements;i++){
        if(i%(numberElements/5)==0) cout<<"* ";
        //Reads each vertex/node's info
        nFile>>c>>id>>c>>latitude>>c>>longitude>>c;
        addVertex(id,latitude,longitude, nullptr);

    }
    int v1,v2;
    cout<<"50% ";
    eFile>>numberElements;

    for(int i=0;i<numberElements;i++){
        if(i%(numberElements/6)==0) cout<<"* ";
        eFile>>c>>v1>>c>>v2>>c;
        addEdge(v1,v2);
    }

    string type;
    int tags;
    tFile>>tags;
    for(int i=0;i<tags;i++){
        if(i%6==0) cout<<"* ";
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
        cout<<"100%"<<endl;
    }

}
/* ================================================================================================
 * Kosaraju
 * ================================================================================================
 */

stack<Vertex*> Graph::AStar(Vertex *start, Vertex *end) {
    vector<Vertex*> discoveredNodes;
    discoveredNodes.push_back(start);
    map<Vertex*,Vertex*> cameFrom;
    map<Vertex*,double> costMap;
    map<Vertex*,double> guessMap;
    for(auto v:vertexSet){
        costMap[v]=INF;
        guessMap[v]=INF;
    }
    costMap[start]=0;
    guessMap[start]=heuristic(start,end);
    while(!discoveredNodes.empty()){
        Vertex* current;
        double min=INF;
        vector<Vertex*>::iterator it=discoveredNodes.begin();
        vector<Vertex*>::iterator toErase;
        while(it!=discoveredNodes.end()){
            if(guessMap[*it]<min){
                min=guessMap[*it];
                current=*it;
                toErase=it;
            }
            it++;
        }
        if(current==end){
            return reconstructPath(cameFrom,current,start);
        }
        discoveredNodes.erase(toErase);
        for(auto edge:current->outgoingEdges){
            double tentative=costMap[current]+edge.weight;
            if(tentative<costMap[edge.dest]){
                cameFrom[edge.dest]=current;
                costMap[edge.dest]=tentative;
                guessMap[edge.dest]=costMap[edge.dest]+ heuristic(current,end);
                bool exists=false;
                for(auto d:discoveredNodes){
                    if(d==edge.dest){
                        exists=true;
                    }
                }
                if(!exists) discoveredNodes.push_back(edge.dest);
            }
        }

    }
    return {};
}

double Graph::heuristic(Vertex *start, Vertex *end) {
    return distanceBetweenCoords(start->getLatitude(),end->getLatitude(),start->getLongitute(),end->getLongitute());
}

stack<Vertex *> Graph::reconstructPath(map<Vertex *, Vertex *> cameFrom, Vertex *current,Vertex *start) {
    stack<Vertex*> path;
    path.push(current);
    while(current!=start){
        current=cameFrom[current];
        path.push(current);
    }

    return path;
}

queue<Vertex *> Graph::nearestNeighbour(vector<Vertex*> pointsTravel){

}

/*-----------------TARJAN----------------------------------------------------------------*/
/*
vector<vector<int>> Graph::kosaraju() {
    stack<Vertex*> L;
    for (Vertex * vertex : vertexSet) {
        vertex->index = NULL;
    }
    vector<vector<int>> scc;
    for (Vertex* vertex : vertexSet) {
        if (vertex->index == NULL) {
            strongConnectedComponent(vertex, scc);
        }
    }
    return scc;
}
void Graph::DFS_Kosaraju(Vertex* src, int nid, stack<Vertex*> &L, vector<vector<int>> &scc) {
    if (S.find(u) != S.end()) return;
    S.insert(u);
    for (node_t v : G->getAdj(u)) DFS_K(v);
    L.push(u);
}
void Graph:: assign(){
    if (SCCs.find(u) != SCCs.end()) return;
    SCCs[u] = root;
    DUGraph temp = G->getTranspose();
    for (node_t v : temp.getAdj(u)) {
        assign(v, root);
    }
}*/
/* ================================================================================================
 * Tarjan
 * ================================================================================================
 */

bool findStackElement (stack<Vertex*> stackV, Vertex * vertex)
{
    while (!stackV.empty() && stackV.top() != vertex){
        stackV.pop();
    }

    if (!stackV.empty())
        return true;

    return false;
}

vector<vector<int>> Graph::tarjan() {
    for (Vertex * vertex : vertexSet) {
        vertex->index = NULL;
    }

    vector<vector<int>> scc;

    for (Vertex* vertex : vertexSet) {
        if (vertex->index == NULL) {
            strongConnectedComponent(vertex, scc);
        }
    }

    return scc;
}

void Graph::strongConnectedComponent(Vertex* src, vector<vector<int>> &scc) {
    int nid = 1;
    stack<Vertex*> L;

    DFS_Tarjan(src, nid, L, scc);
}

void Graph::DFS_Tarjan(Vertex* src, int nid, stack<Vertex*> &L, vector<vector<int>> &scc){
    L.push(src);
    src->index = nid++;
    src->low = nid;

    for (Edge edge : src->getOutgoingEdges()) {
        if (edge.dest->index == NULL) {
            DFS_Tarjan(edge.dest, nid, L, scc);
            src->low = min(src->low, edge.dest->low);
        } else if (findStackElement(L, edge.dest)) {
            src->low = min(src->low, edge.dest->index);
        }
    }

    if (src->low == src->index) {
        vector<int> sc;
        Vertex * v;
        do {
            v = L.top();
            L.pop();
            sc.push_back(v->getID());
        } while (v != src);
        scc.push_back(sc);
    }
}

vector<int> Graph::largestSCC() {
    vector<vector<int>> scc_list = tarjan();
    cout << "Total number of strongly connected components: " << scc_list.size() << endl;
    int majorSize = 0;
    int index = -1;
    for(int i = 0; i < scc_list.size(); i++){
        if(scc_list.at(i).size() > majorSize){
            majorSize = scc_list.at(i).size();
            index = i;
        }
    }
    return scc_list.at(index);
}

void Graph::preprocessGraph() {
    bool remove;
    auto strongComponent= largestSCC();
    for(auto v:vertexSet){
        remove=true;
        for(auto id:strongComponent){
            if(v->getID()==id){
                remove=false;
                break;
            }
        }
        if(remove) removeVertex(v->getLatitude(),v->getLongitute());
    }
}

vector<vector<int>> Graph::kosaraju() {
    stack<Vertex*> L;
    unordered_set<Vertex*> S;
    vector<vector<int>> SCC;
    for (Vertex * vertex : vertexSet) {
        vertex->index = NULL;
    }

    for (Vertex * vertex : vertexSet) {
        DFS_Kosaraju(vertex, L, S);
    }

    while(!L.empty()){
        Vertex *vertex = L.top();
        L.pop();
        vector<int> sc;
        assign(vertex, vertex, sc);
        SCC.push_back(sc);
    }

    return SCC;
}

void Graph::DFS_Kosaraju(Vertex *src, stack<Vertex*> &L, unordered_set <Vertex *> S) {
    if (S.find(src) != S.end()) return;
    S.insert(src);
    for(Edge e : src->getOutgoingEdges()) {
        DFS_Kosaraju(e.dest, L, S);
    }
    L.push(src);
}

void Graph::assign(Vertex *u, Vertex *root, vector<int> &sc) {
    vector<int>:: iterator it;
    it = find(sc.begin(), sc.end(), u->getID());
    if(it != sc.end()) return;
    sc.push_back(root->getID());
    Graph temp = getTransposedGraph();
    for (Edge e : temp.findVertex(u->ID)->getOutgoingEdges()) {
        assign(e.dest, root,sc);
    }
}

Graph Graph::getTransposedGraph() const {
    Graph transposedGraph;
    for(const Vertex *v : vertexSet) transposedGraph.addVertex(v->ID, v->latitude, v->longitude, v->info);
    for(Vertex *v : vertexSet){
        for( const Edge e : v->getOutgoingEdges()){
            transposedGraph.addEdge(e.dest->getLatitude(), e.dest->getLongitute(),v->getLatitude(),v->getLongitute());
        }
    }
    return transposedGraph;
}