//
// Created by migue on 17/05/2021.
//

#ifndef WASTE_APP_GRAPHVIEW_H
#define WASTE_APP_GRAPHVIEW_H

#include "graphviewer.h"
#include "../Graph/Graph.h"

class GraphView {
    Graph graph;
public:
    GraphView(Graph graph): graph(graph){
    //    GraphViewer graphViewer;
        /*for(auto v:graph.getVertexSet()){
            graphViewer.addNode()
        }*/
    }
};


#endif //WASTE_APP_GRAPHVIEW_H
