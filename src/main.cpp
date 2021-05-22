#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Graph/Graph.h"
#include "Elements/App.h"
#include "UI/Menu.h"
#include "UI/UI.h"


#include "Algorithms/Preprocessing.h"

using namespace std;

int main() {
    Graph graph("../Map/outputTarjan/processedNodes.txt","../Map/outputKosaraju/processedEdges.txt");
    //Graph graph("../Map/porto_full_nodes_xy.txt","../Map/porto_full_edges.txt");
    //Preprocessing::preprocessGraphKosaraju(graph,"../Map/porto_full_nodes_xy.txt","../Map/porto_full_nodes_xy.txt");

    App app(graph);
    app.aStarAnalysis();
    /*UI ui(&graph, 1600, 900);
    ui.showGraph();*/
    //Initializing initializing(graph);
    //graph.preprocessGraph();

    //UI ui(&graph, 1600, 900);
    //ui.showGraph();
    //cout<<"terminei";
    //Menu::mainMenu();
    return 0;
}

