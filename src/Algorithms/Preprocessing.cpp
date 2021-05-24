//
// Created by miguel on 21/05/21.
//

#include "Preprocessing.h"

/* ================================================================================================
 * Tarjan
 * ================================================================================================
 */
bool Preprocessing::findStackElement(stack<Vertex *> stackV, Vertex *vertex) {
    while (!stackV.empty() && stackV.top() != vertex){
        stackV.pop();
    }

    if (!stackV.empty())
        return true;

    return false;
}

vector<vector<int>> Preprocessing::tarjan(Graph graph) {
    for (Vertex * vertex : graph.getVertexSet()) {
        vertex->setIndex(-1);
        vertex->setLow(-1);
    }
    vector<vector<int>> scc;
    stack<Vertex*> L;
    int index = 0;
    for (Vertex* vertex : graph.getVertexSet()) {
        if (vertex->getIndex() == -1) {
            DFS_Tarjan(vertex, index, L, scc);
        }
    }
    return scc;
}

void Preprocessing::DFS_Tarjan(Vertex *src, int &index, stack<Vertex *> &L, vector<vector<int>> &scc) {
    //// Set the depth index for v to the smallest unused index
    src->setIndex(index);
    src->setLow(index);
    index++;
    L.push(src);
    //// Consider successors of v
    for (Edge edge : src->getOutgoingEdges()) {
        if (edge.getDest()->getIndex() == -1) {
            //// Successor has not yet been visited; recurse on it
            DFS_Tarjan(edge.getDest(), index, L, scc);
            src->setLow(min(src->getLow(), edge.getDest()->getLow()));
        } else if (findStackElement(L, edge.getDest())) {
            //// Successor w is in stack S and hence in the current SCC
            src->setLow( min(src->getLow(), edge.getDest()->getIndex()));
        }
    }
    //// If src is a root node, pop the stack and generate an SCC
    if (src->getLow() == src->getIndex()) {
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

vector<int> Preprocessing::largestSCCTarjan(Graph graph) {
    vector<vector<int>> scc_list = tarjan(graph);
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
vector<vector<int>> Preprocessing::kosaraju(Graph graph) {
    stack<Vertex*> L;
    unordered_set<Vertex*> S1;
    unordered_set<Vertex*> S2;

    vector<vector<int>> SCCs;
    ////STEP 1: Perfome DFS traversal and push nodes to the stack
    for (Vertex * vertex : graph.getVertexSet()) {
        if(S1.find(vertex) == S1.end()) DFS_Kosaraju(vertex, L, S1);
    }

    ////STEP 2: Find the transposed graph by reversing the edges
    Graph transposedGraph = getTransposedGraph(graph);

    for(Vertex * vertex : transposedGraph.getVertexSet()){
        cout << vertex->getID() << endl;
    }
    for(Vertex * vertex : transposedGraph.getVertexSet()){
        for(Edge edge : vertex->getOutgoingEdges()){
            cout << vertex->getID() << " -> " << edge.getDest()->getID() << endl;
        }
    }
    ////STEP 3: Pop nodes one by one from stack
    vector<int> scc;
    while(!L.empty()){
        for (auto const &i: S2) {
            cout << i->getID() << " ";
        }
        cout << endl;
        Vertex * vertex = L.top();
        L.pop();
        scc.clear();
        DFS_2(vertex, S2, scc, transposedGraph);
        if(!scc.empty()) {
            SCCs.push_back(scc);
        }
    }
    return SCCs;
}

void Preprocessing::DFS_Kosaraju(Vertex *src, stack<Vertex*> &L, unordered_set <Vertex *> &S) {
    if (S.find(src) != S.end()) return;
    S.insert(src);
    for(Edge e : src->getOutgoingEdges()) {
        DFS_Kosaraju(e.getDest(), L, S);
    }
    L.push(src);
}

void Preprocessing::DFS_2(Vertex *src, unordered_set <Vertex *> &S, vector <int> &scc, Graph transposedGraph) {
    if (S.find(transposedGraph.findVertex(src->getID())) != S.end()) return; ////is already visited
    S.insert(transposedGraph.findVertex(src->getID()));
    scc.push_back(src->getID());
    for (Edge edge :transposedGraph.findVertex(src->getID())->getOutgoingEdges()) {
        DFS_2(edge.getDest(), S, scc, transposedGraph);
    }
}

Graph Preprocessing::getTransposedGraph(Graph graph){
    Graph transposedGraph;
    for(Vertex *v : graph.getVertexSet()) transposedGraph.addVertex(v->getID(), v->getX(), v->getY());
    for(Vertex *v : graph.getVertexSet()){
        for( Edge e : v->getOutgoingEdges()){
            transposedGraph.addEdge(e.getDest()->getX(), e.getDest()->getY(), v->getX(), v->getY());
        }
    }
    return transposedGraph;
}

vector<int> Preprocessing::largestSCCKosaraju(Graph graph) {
    vector<vector<int>> scc_list = kosaraju(graph);
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
 * Pre-Processing
 * ================================================================================================
 */

void Preprocessing::preprocessGraphTarjan(Graph graph,string nodePath,string edgesPath) {
    vector<int> strongComponent = largestSCCTarjan(graph);
    preprocess(graph, nodePath, edgesPath, strongComponent);
}

void Preprocessing::preprocessGraphKosaraju(Graph graph, string nodePath, string edgesPath){
    vector<int> strongComponent = largestSCCKosaraju(graph);
    preprocess(graph, nodePath, edgesPath, strongComponent);
}

void Preprocessing::preprocess(Graph graph, string nodePath, string edgesPath, vector<int> strongComponent) {
    //cout << "Size of Larger SCC "  << strongComponent.size() << endl;
    stack<int> toRemove;
    int i=0,k=0;
    bool remove;
    for(Vertex* v:graph.getVertexSet()){
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
    //cout<<"Number of edges that will be removed: " << toRemove.size()<< endl;
    while(!toRemove.empty()){
        if(!graph.removeVertex(toRemove.top())){
            cout<<"e\n"<<endl;
            i++;
        }
        toRemove.pop();
    }
    createSCCFile(nodePath, edgesPath,graph);
}

void Preprocessing::createSCCFile(string fileNodes, string fileEdges,Graph graph) {
    ofstream nodeFile(fileNodes),edgeFile(fileEdges);
    nodeFile<<graph.getNumVertex()<<"\n";
    int edges=0;
    for (auto v:graph.getVertexSet()){
        nodeFile<<setprecision(17)<<"("<<v->getID()<<","<<v->getX()<<","<<v->getY()<<")\n";
        edges+=v->getOutgoingEdges().size();
    }
    edgeFile<<edges<<"\n";
    for (auto v:graph.getVertexSet()){
        for(auto e:v->getOutgoingEdges()){
            edgeFile<<setprecision(17)<<"("<<v->getID()<<","<<e.getDest()->getID()<<")\n";
        }
    }
}

/* ================================================================================================
 * Test Preprocessing Algorithms
 * ================================================================================================
 */
void Preprocessing::testTarjan(){
    //Initializes a full graph
    Graph graph("../Map/testSCC/testNodes.txt","../Map/testSCC/testEdges.txt");

    cout<< "===================================="<<endl;
    cout<< "           TESTING TARJAN           "<<endl;
    cout<< "===================================="<<endl;

    //Runs Tarjan's algorithm
    vector<vector<int>> scc = tarjan(graph);

    for(int i = 0; i < scc.size(); i++){
        for(int j = 0; j < scc.at(i).size(); j++){
            cout << scc.at(i).at(j) << " ";
        }
        cout << endl;
    }
    cout << "You should have " << 4 << " strong connected components" << endl;
    cout << "You have : " << scc.size() <<  " strong connected components" << endl;
}

void Preprocessing::testKosaraju(){
    //Initializes a full graph
    Graph graph("../Map/testSCC/testNodes.txt","../Map/testSCC/testEdges.txt");

    cout<< "===================================="<<endl;
    cout<< "         TESTING KOSARAJU           "<<endl;
    cout<< "===================================="<<endl;

    //Runs Kosaraju's algorithm
    vector<vector<int>> scc = kosaraju(graph);

    for(int i = 0; i < scc.size(); i++){
        for(int j = 0; j < scc.at(i).size(); j++){
            cout << scc.at(i).at(j) << " ";
        }
        cout << endl;
    }

    cout << "You should have " << 4 << " strong connected components" << endl;
    cout << "You have : " << scc.size() <<  " strong connected components" << endl;
}