#include <iostream>
#include "Graph/Graph.h"


using namespace std;
int main() {
    Graph graph("../Map/nodes_lat_lon_porto.txt","../Map/edges_porto.txt","../Map/t02_tags_porto.txt");
    return 0;
}
