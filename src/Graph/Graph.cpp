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

double Graph::distanceBetweenCoords(double x1, double x2, double y1, double y2) {
    //uses the Haversine formula to calcuxe distances in a sphere
    /*double dYg = (y2 - y1) * degreeToRadian;
    double dX = (x2 - x1) * degreeToRadian;
    double a = pow(sin(dX / 2.0), 2) + cos(x1 * degreeToRadian) * cos(x2 * degreeToRadian) * pow(sin(dYg / 2.0), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = 6371 * c; //6371 is the Earth's radius
    return d;*/

    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
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
    double d=distanceBetweenCoords(v1->getX(), v2->getX(), v1->getY(), v2->getY());
    v1->addEdge(v2, d);
    return true;
}


Graph::Graph(string nodesFile, string edgesFile) {
    cout<< "===================================="<<endl;
    cout<< "         LOADING THE GRAPH          "<<endl;
    cout<< "===================================="<<endl;
    cout<<"0% ";
    ifstream nFile(nodesFile),eFile(edgesFile);

    int numberElements;
    char c;

    int id;
    double x,y;

    //Reads number of nodes
    nFile>>numberElements;
    for(int i=0;i<numberElements;i++){
        if(i%(numberElements/6)==0) cout<<"* ";
        //Reads each vertex/node's info
        nFile>>c>>id>>c>>x>>c>>y>>c;
        addVertex(id,x,y);
    }

    int v1,v2;
    cout<<"50% ";
    eFile>>numberElements;

    for(int i=0;i<numberElements;i++){
        if(i%(numberElements/6)==0) cout<<"* ";
        eFile>>c>>v1>>c>>v2>>c;
        addEdge(v1,v2);
    }
    cout<<"100%"<<endl;
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

stack<Vertex*> Graph::aStar(Vertex *start, Vertex *end) {
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
    return distanceBetweenCoords(start->getX(), end->getX(), start->getY(), end->getY());
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

queue<Vertex *> Graph::nearestNeighbour(double x,double y,vector<Vertex*> pointsTravel){
    queue<Vertex*> orderedCompletePath;
    Vertex *initialVertex = findClosestVertex(x,y);
    orderedCompletePath.push(initialVertex);
    double minDistance;
    stack<Vertex*> next;
    vector<Vertex*>::iterator copy;
    while(!pointsTravel.empty()) {
        minDistance=INF;
        for (auto it = pointsTravel.begin(); it != pointsTravel.end(); it++) {
            auto path = aStar(initialVertex, (*it));
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
        vertex->index = 0;
    }

    vector<vector<int>> scc;

    for (Vertex* vertex : vertexSet) {
        if (vertex->index == 0) {
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
        if (edge.dest->index == 0) {
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

/* ================================================================================================
 * Pre Process Graph
 * ================================================================================================
 */
void Graph::preprocessGraph() {
    vector<int> strongComponent = this->largestSCC();
    stack<int> toRemove;
    int i=0,k=0;
    bool remove;
    for(Vertex* v:vertexSet){
        remove=true;
        for(int j=0;j<strongComponent.size();j++){
            if(v->getID()==strongComponent[j]) {
                remove=false;
                break;
            }
        }
        if(remove==true) {
            toRemove.push(v->getID());
            k++;
        };
    }
    cout<<toRemove.size()<<"\n";
    while(!toRemove.empty()){

        if(!removeVertex(toRemove.top())){
            cout<<"e\n"<<endl;
            i++;
        }
        toRemove.pop();
    }
    cout<<i;
    ofstream nodeFile("../Map/processedNodes.txt"),edgeFile("../Map/processedEdges.txt");
    nodeFile<<vertexSet.size()<<"\n";
    int edges=0;
    for (auto v:vertexSet){
        nodeFile<<setprecision(17)<<"("<<v->getID()<<","<<v->getX()<<","<<v->getY()<<")\n";
        edges+=v->getOutgoingEdges().size();
    }
    edgeFile<<edges<<"\n";
    for (auto v:vertexSet){
        for(auto e:v->getOutgoingEdges()){
            edgeFile<<setprecision(17)<<"("<<v->getID()<<","<<e.dest->getID()<<")\n";
        }
    }
}

Vertex *Graph::findClosestVertex(double x, double y) {
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

double Graph::pathCost(stack<Vertex *> path) {
    if(path.size()<2) return 0;
    double cost=0;
    auto v=path.top();
    path.pop();
    while(!path.empty()){
        for(auto e:v->getOutgoingEdges()){
            if(e.dest==path.top()){
                cost+=e.weight;
                break;
            }
        }
        v=path.top();
        path.pop();
    }
    return cost;
}

stack<Vertex *> Graph::dijkstra(Vertex *start, Vertex *end) {
    map <Vertex*,Vertex*> cameFrom;
    for(auto v:vertexSet){
        v->distance=INF;
        v->queueIndex=0;
    }
    start->distance=0;
    MutablePriorityQueue<Vertex*> queue;
    queue.insert(start);
    Vertex* v;
    while(!queue.empty()){
        v=queue.extractMin();
        if(v==end) break;
        for(auto e:v->outgoingEdges){
            double d=v->distance+e.weight;
            if(d<e.dest->distance){
                e.dest->distance=d;
                cameFrom[e.dest]=v;
                queue.insertOrDecreaseKey(e.dest);
            }
        }
    }
    return reconstructPath(cameFrom,end,start);

}
