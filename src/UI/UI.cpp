//
// Created by sofia on 19/05/21.
//
/*
#include "UI.h"

UI::UI(Graph * graph, int width, int height) : graph(graph), graphViewerHeight(graphViewerHeight), graphViewerWidth(graphViewerWidth){}

void UI::showGraph() {
    this->graphViewer = new GraphViewer();
    graphViewer->createWindow(graphViewerWidth, graphViewerHeight);

    for (Vertex * vertex : graph->getVertexSet()) {
        graphViewer->addNode(vertex->getID(), sf::Vector2f (vertex->getX(), vertex->getY()));
    }

    int id = 0;
    for (Vertex* vertex : graph->getVertexSet()) {
        for (Edge edge : vertex->getOutgoingEdges()) {
            graphViewer->addEdge(id, graphViewer->getNode(vertex->getID()), graphViewer->getNode(edge.getDest()->getID()), GraphViewer::Edge::EdgeType::DIRECTED);
            id++;
        }
    }
}*/