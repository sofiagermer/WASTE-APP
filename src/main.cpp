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
    Menu::frontpage();

    Graph graph("../Map/sccGiven/porto_strong_nodes_xy.txt","../Map/sccGiven/porto_strong_edges.txt");
    App app(&graph);
    UI ui(&graph,300,300);
    Menu menu(app, ui);
    menu.mainMenu();
    return 0;
}

