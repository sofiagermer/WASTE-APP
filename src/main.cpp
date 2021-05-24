#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Graph/Graph.h"
#include "Elements/App.h"
#include "UI/Menu.h"
#include "UI/UI.h"


#include "Algorithms/Preprocessing.h"

using namespace std;
//App app;

int main() {
    //App app(graph);
    //app.aStarAnalysis();
    /*UI ui(&graph, 1600, 900);
    ui.showGraph();*/
    //Initializing initializing(graph);
    //graph.preprocessGraph();

    //UI ui(&graph, 1600, 900);
    //ui.showGraph();
    //cout<<"terminei";
    Menu::frontpage();
   // Graph graph("../Map/sccGiven/porto_strong_nodes_xyy.txt","../Map/sccGiven/porto_strong_edges.txt");
    Graph graph("../Map/outputTarjan/processedNodes.txt","../Map/outputTarjan/processedEdges.txt");
    App app(&graph);
    UI ui(&graph,300,300);
        //ui.showGraph();
    //ui.showGraph();
    Menu menu(app, ui);
    menu.mainMenu();
    return 0;
}

