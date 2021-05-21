//
// Created by miguel on 21/05/21.
//

#include "Preprocessing.h"

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

void Preprocessing::preprocessGraphTarjan(Graph graph,string nodePath,string edgesPath) {
    //vector<int> strongComponent = this->largestSCCKosaraju();
    vector<int> strongComponent = largestSCCTarjan(graph);
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
    //createSCCFile("../Map/outputKosaraju/processedNodes.txt", "../Map/outputKosaraju/processedEdges.txt");
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
