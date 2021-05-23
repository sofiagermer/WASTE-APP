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

    static void DFS_Tarjan(Vertex* src, int &index, stack<Vertex*> &L, vector<vector<int>> &scc);

    static vector<int> largestSCCTarjan(Graph graph);

    static void createSCCFile(string fileNodes, string fileEdges,Graph graph);

    //KOSARAJU
    static vector<vector<int>> kosaraju(Graph graph);
    static void DFS_Kosaraju(Vertex *src, stack<Vertex*> &L, unordered_set <Vertex *> &S);
    static void DFS_2(Vertex *src, unordered_set <Vertex *> &S, vector <int> &sc);
    static Graph getTransposedGraph(Graph graph);
    static vector<int> largestSCCKosaraju(Graph graph);
public:

    static void preprocessGraphTarjan(Graph graph, string nodePath, string edgesPath);
    static void preprocessGraphKosaraju(Graph graph, string nodePath, string edgesPath);
    static void preprocess(Graph graph, string nodePath, string edgesPath,vector<int> strongComponent);
};


#endif //WASTE_APP_PREPROCESSING_H
