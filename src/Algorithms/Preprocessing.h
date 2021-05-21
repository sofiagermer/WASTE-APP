//
// Created by miguel on 21/05/21.
//

#ifndef WASTE_APP_PREPROCESSING_H
#define WASTE_APP_PREPROCESSING_H


#include "../Graph/Graph.h"

class Preprocessing {
private:
    static bool findStackElement (stack<Vertex*> stackV, Vertex * vertex);

    static vector<vector<int>> tarjan(Graph graph);

    static void strongConnectedComponent(Vertex* src, vector<vector<int>> &scc);

    static void DFS_Tarjan(Vertex* src, int nid, stack<Vertex*> &L, vector<vector<int>> &scc);

    static vector<int> largestSCCTarjan(Graph graph);

    static void createSCCFile(string fileNodes, string fileEdges,Graph graph);
public:

    static void preprocessGraphTarjan(Graph graph, string nodePath, string edgesPath);



};


#endif //WASTE_APP_PREPROCESSING_H
