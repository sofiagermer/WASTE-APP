#include <iostream>
#include <iomanip>
#include "Graph/Graph.h"


using namespace std;
int main() {
    Graph graph("../Map/porto_full_nodes_latlng.txt","../Map/porto_full_edges.txt","../Map/tags.txt");
    return 0;
}
