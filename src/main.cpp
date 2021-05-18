#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Graph/Graph.h"
#include "UI/Menu.h"



using namespace std;

int main() {

    Graph graph("../Map/porto_full_nodes_latlng.txt","../Map/porto_full_edges.txt","../Map/tags.txt");
    graph.preprocessGraph();
    cout<<"terminei";
    return 0;
}

