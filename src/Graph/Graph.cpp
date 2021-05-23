#include "Graph.h"




/* ================================================================================================
 * Vertex
 * ================================================================================================
 */
Vertex::Vertex(int id, double x, double y): x(x), y(y), ID(id){}

Vertex *Edge::getDest() {
    return dest;
}

Vertex * Graph::findVertex(double x, double y) {
    for (auto v : vertexSet)
        if (v->x == x && v->y == y)
            return v;
    return NULL;
}

void Vertex::addEdge(Vertex *d, double w) {
    outgoingEdges.push_back(Edge(d,w));
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

double Vertex::getX() {
    return x;
}

double Vertex::getY() {
    return y;
}

int Vertex::getID(){
    return this->ID;
}

vector<Edge> Vertex::getOutgoingEdges() {
    return outgoingEdges;
}

/* ================================================================================================
 * Edge
 * ================================================================================================
 */
Edge::Edge(Vertex *d, double w): dest(d), weight(w) {}


/* ================================================================================================
 * Graph
 * ================================================================================================
 */
int Graph::getNumVertex() const {
    return vertexSet.size();
}

bool Graph::addVertex(int id,double x, double y) {
    if(findVertex(x,y)!=NULL)
        return false;
    vertexSet.push_back(new Vertex(id,x,y));
    return true;
}

bool Graph::addEdge(double sourceX, double sourceY, double destX, double destY) {
    if(findVertex(sourceX,sourceY)==NULL||findVertex(destX,destY)==NULL)
        return false;
    auto v1= findVertex(sourceX,sourceY);
    double d=distanceBetweenCoords(sourceX,destX,sourceY,destY);
    v1->addEdge(findVertex(destX,destY), d);
    return true;
}

bool Graph::removeEdge(double sourceX, double sourceY, double destX, double destY) {
    auto *v1=findVertex(sourceX,sourceY);
    auto *v2=findVertex(destX,destY);
    if(v1==NULL||v2==NULL) return false;
    return v1->removeEdgeTo(v2);
}

bool Vertex::operator<(Vertex *v) {
    return this->distance<v->distance;
}

int Vertex::getIndex() const {
    return index;
}

void Vertex::setIndex(int index) {
    Vertex::index = index;
}

int Vertex::getLow() const {
    return low;
}

void Vertex::setLow(int low) {
    Vertex::low = low;
}

double Vertex::getDistance() const {
    return distance;
}

void Vertex::setDistance(double distance) {
    Vertex::distance = distance;
}

int Vertex::getQueueIndex() const {
    return queueIndex;
}

void Vertex::setQueueIndex(int queueIndex) {
    Vertex::queueIndex = queueIndex;
}

bool Graph::removeVertex(double x, double y) {
    auto v=findVertex(x,y);
    if(v==NULL) return false;
    typename std::vector<Vertex*>::iterator it;
    auto copy=vertexSet.begin();
    for(it=vertexSet.begin();it!=vertexSet.end();it++){
        if((*it)->x == x && (*it)->y == y){
            copy=it;
            continue;
        }
        (*it)->removeEdgeTo(v);
    }
    vertexSet.erase(copy);
    return true;
}

double distanceBetweenCoords(double x1, double x2, double y1, double y2);

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
    double d=distanceBetweenCoords(v1->getX(), v2->getX(), v1->getY(), v2->getY());
    v1->addEdge(v2, d);
    return true;
}


Graph::Graph(string nodesFile, string edgesFile) {
    cout<< "===================================="<<endl;
    cout<< "         LOADING THE GRAPH          "<<endl;
    cout<< "===================================="<<endl;
    cout<<"0% "<<flush;
    ifstream nFile(nodesFile),eFile(edgesFile);

    int numberElements;
    char c;

    int id;
    double x,y;

    //Reads number of nodes
    nFile>>numberElements;
    for(int i=0;i<numberElements;i++){
        if(i%(numberElements/6)==0) cout<<"* "<<flush;
        //Reads each vertex/node's info
        nFile>>c>>id>>c>>x>>c>>y>>c;
        addVertex(id,x,y);
    }

    int v1,v2;
    cout<<"50% ";
    eFile>>numberElements;

    for(int i=0;i<numberElements;i++){
        if(i%(numberElements/6)==0) cout<<"* "<<flush;
        eFile>>c>>v1>>c>>v2>>c;
        addEdge(v1,v2);
    }
    cout<<"100%"<<endl;
}

Vertex * Graph::findClosestVertex(double x, double y) {
    Vertex *closest= nullptr;
    double min=INF;
    for(auto v:vertexSet){
        double aux;
        if((aux=distanceBetweenCoords(v->getX(),x,v->getY(),y))<min){
            closest=v;
            min=aux;
        }
    }
    return closest;
}


/* ================================================================================================
 *
 *
 *
 *                                      ALGORITHMS
 *
 *
 * ================================================================================================
 */


/* ================================================================================================
 * A Star
 * ================================================================================================
 */



/* ================================================================================================
 * Tarjan
 * ================================================================================================
 */


/* ================================================================================================
 * Kosaraju
 * ================================================================================================
 */

vector<vector<int>> Graph::kosaraju() {
    stack<Vertex*> L;
    unordered_set<Vertex*> S;
    vector<vector<int>> SCC;
    for (Vertex * vertex : vertexSet) {
        vertex->index = 0;
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
    for(const Vertex *v : vertexSet) transposedGraph.addVertex(v->ID, v->x, v->y);
    for(Vertex *v : vertexSet){
        for( const Edge e : v->getOutgoingEdges()){
            transposedGraph.addEdge(e.dest->getX(), e.dest->getY(), v->getX(), v->getY());
        }
    }
    return transposedGraph;
}

bool Graph::removeVertex(int id) {
    auto v=findVertex(id);
    if(v==NULL) return false;
    typename std::vector<Vertex*>::iterator it;
    auto copy=vertexSet.begin();
    for(it=vertexSet.begin();it!=vertexSet.end();it++){
        if((*it)->getID()==id){
            copy=it;
            continue;
        }
        (*it)->removeEdgeTo(v);
    }
    vertexSet.erase(copy);
    free(v);
    return true;
}

vector<int> Graph::largestSCCKosaraju() {
    vector<vector<int>> scc_list = kosaraju();
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

double Graph::distanceBetweenCoords(double x1, double x2, double y1, double y2) {
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

double Edge::getWeight() const {
    return weight;
}
/* ================================================================================================
 * Pre Process Graph
 * ================================================================================================
 */


