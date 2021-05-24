//
// Created by sofia on 19/05/21.
//

#ifndef WASTE_APP_UI_H
#define WASTE_APP_UI_H

#include <graphviewer.h>
#include "../Graph/Graph.h"
#include "../Elements/TrashContainer.h"

class UI {
    Graph *graph;
    GraphViewer *graphViewer;

    int graphViewerHeight;
    int graphViewerWidth;

public:
    UI(Graph * graph, int width, int height);

    void showGraph();

    void showTrashContainer(double userX,double userY, Vertex *trashContainer, TrashType type);
};


#endif //WASTE_APP_UI_H