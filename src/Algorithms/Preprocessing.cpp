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
        vertex->setIndex(0);
    }

    vector<vector<int>> scc;

    for (Vertex* vertex : graph.getVertexSet()) {
        if (vertex->getIndex() == 0) {
            strongConnectedComponent(vertex, scc);
        }
    }

    return scc;
}

void Preprocessing::strongConnectedComponent(Vertex *src, vector<vector<int>> &scc) {
    int nid = 1;
    stack<Vertex*> L;

    DFS_Tarjan(src, nid, L, scc);
}

void Preprocessing::DFS_Tarjan(Vertex *src, int nid, stack<Vertex *> &L, vector<vector<int>> &scc) {
    L.push(src);
    src->setIndex(nid++);
    src->setLow(nid);

    for (Edge edge : src->getOutgoingEdges()) {
        if (edge.getDest()->getIndex() == 0) {
            DFS_Tarjan(edge.getDest(), nid, L, scc);
            src->setLow(min(src->getLow(), edge.getDest()->getLow()));
        } else if (findStackElement(L, edge.getDest())) {
            src->setLow( min(src->getLow(), edge.getDest()->getIndex()));
        }
    }

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
    //STEP 1: Perfome DFS traversal and push nodes to the stack
    for (Vertex * vertex : graph.getVertexSet()) {
        DFS_Kosaraju(vertex, L, S1);
    }

    //STEP 2: Find the transposed graph by reversing the edges
    Graph transposedGraph = getTransposedGraph(graph);
    cout << "fim de transposed graph " << endl;
    //STEP 3: Pop nodes one by one from stack
    vector<int> scc;
    while(!L.empty()){
        Vertex * vertex = L.top();
        L.pop();
        cout << "Tamanho L: " << L.size() << endl;
        scc.clear();
        DFS_2(vertex, S2, scc);
        if(!scc.empty()) {
            cout << "TEMOS UM SCC " << endl;
            SCCs.push_back(scc);
        }
        else{
            cout << "TÁ VAZIA E EU TOU NA MERDA " << endl;
        }
    }
    cout << "Number of SCCs: " << SCCs.size() << endl;
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

void Preprocessing::DFS_2(Vertex *src, unordered_set <Vertex *> &S, vector <int> &sc) {
    if (S.find(src) != S.end()) return;
    S.insert(src);
    sc.push_back(src->getID());
    for (Edge e : src->getOutgoingEdges()) {
        DFS_2(e.getDest(), S, sc);
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

