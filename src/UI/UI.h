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

    void displayRoute(vector <House*> houses, queue <Vertex*> route){
        this->graphViewer = new GraphViewer();

        for (Vertex * vertex : graph->getVertexSet()) {
            graphViewer->addNode(vertex->getID(), sf::Vector2f (vertex->getX(), vertex->getY()));
        }
        while(!route.empty()){
            graphViewer->getNode(route.front()->getID()).setColor(GraphViewer::BLUE);
            route.pop();
        }
        int id = 0;
        for (Vertex* vertex : graph->getVertexSet()) {
            for (Edge edge : vertex->getOutgoingEdges()) {
                if(graphViewer->getNode(vertex->getID()).getColor()==GraphViewer::BLUE && graphViewer->getNode(edge.getDest()->getID()).getColor()==GraphViewer::BLUE){
                    graphViewer->addEdge(id, graphViewer->getNode(vertex->getID()), graphViewer->getNode(edge.getDest()->getID()), GraphViewer::Edge::EdgeType::DIRECTED).setColor(GraphViewer::BLUE);
                }
                graphViewer->addEdge(id, graphViewer->getNode(vertex->getID()), graphViewer->getNode(edge.getDest()->getID()), GraphViewer::Edge::EdgeType::DIRECTED);
                id++;
            }
        }
        graphViewer->createWindow(graphViewerWidth, graphViewerHeight);
    }
};


#endif //WASTE_APP_UI_H