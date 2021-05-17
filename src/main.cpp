#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Graph/Graph.h"
#include "UI/Menu.h"

vector<int> largestSCC(Graph &graph) {
    vector<vector<int>> scc_list = graph.tarjan();
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

using namespace std;
int main() {
    /*
    Graph graph("../Map/porto_full_nodes_latlng.txt","../Map/porto_full_edges.txt","../Map/tags.txt");
    vector <int> strongComponent = largestSCC(graph);
    cout << strongComponent.size() << endl;
    for(auto elem : strongComponent){
        cout << elem << endl;
    }*/
    Menu::mainMenu();

    return 0;
}

