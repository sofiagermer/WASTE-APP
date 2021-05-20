#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Graph/Graph.h"
#include "UI/Menu.h"
#include "UI/UI.h"

/*
vector<int> KO(Graph &graph) {
    vector<vector<int>> scc_list = graph.kosaraju();
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
}*/

using namespace std;

int main() {

    Graph graph("../Map/processedNodes.txt","../Map/processedEdges.txt");
    //graph.preprocessGraph();

    /*UI ui(&graph, 1600, 900);
    ui.showGraph();*/
    //Menu::mainMenu();
    return 0;
}

