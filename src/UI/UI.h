//
// Created by sofia on 19/05/21.
//

#ifndef WASTE_APP_UI_H
#define WASTE_APP_UI_H

#include <graphviewer.h>
#include "../Graph/Graph.h"
#include "../Elements/TrashContainer.h"
#include "../Elements/House.h"

class UI {
    Graph *graph;
    GraphViewer *graphViewer;

    int graphViewerHeight;
    int graphViewerWidth;

public:
    UI(Graph * graph, int width, int height);

    void showGraph();

    void showTrashContainer(double userX,double userY, Vertex *trashContainer, TrashType type);

    void displayRoute(vector <House*> houses, queue <Vertex*> route);

    void displayTwoPointRoute(queue <Vertex*> route);
};


#endif //WASTE_APP_UI_H