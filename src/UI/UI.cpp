//
// Created by sofia on 19/05/21.
//

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
}

void UI::showTrashContainer(double userX, double userY, TrashContainer *trashContainer) {
    this->graphViewer = new GraphViewer();
    graphViewer->setCenter(sf::Vector2f(userX, userY));
    auto maxDist=graph->distanceBetweenCoords(userX,trashContainer->getVertex()->getX(),userY,trashContainer->getVertex()->getY());
    maxDist=maxDist*1.5;

    for (Vertex * vertex : graph->getVertexSet()) {
        if(graph->distanceBetweenCoords(vertex->getX(),trashContainer->getVertex()->getX(),vertex->getY(),trashContainer->getVertex()->getY())>maxDist)
            continue;
        if(vertex->getID()==trashContainer->getVertex()->getID()){
            auto node=graphViewer->addNode(vertex->getID(), sf::Vector2f (vertex->getX(), vertex->getY()));
            switch (trashContainer->getType()) {
                case Paper:
                    node.setColor(GraphViewer::BLUE);
                    break;
                case Plastic:
                    node.setColor(GraphViewer::YELLOW);
                    break;
                case Glass:
                    node.setColor(GraphViewer::GREEN);
                    break;
                case Regular:
                    node.setColor(GraphViewer::GRAY);
                    break;
                default:
                    break;
            }
            continue;
        }
        graphViewer->addNode(vertex->getID(), sf::Vector2f (vertex->getX(), vertex->getY()));
    }

    int id = 0;
    for (Vertex* vertex : graph->getVertexSet()) {
        if(graph->distanceBetweenCoords(vertex->getX(),trashContainer->getVertex()->getX(),vertex->getY(),trashContainer->getVertex()->getY())>maxDist)
            continue;
        for (Edge edge : vertex->getOutgoingEdges()) {
            if(graph->distanceBetweenCoords(edge.getDest()->getX(),trashContainer->getVertex()->getX(),edge.getDest()->getY(),trashContainer->getVertex()->getY())>maxDist)
                break;
            graphViewer->addEdge(id, graphViewer->getNode(vertex->getID()), graphViewer->getNode(edge.getDest()->getID()), GraphViewer::Edge::EdgeType::DIRECTED);
            id++;
        }
    }
    graphViewer->createWindow(graphViewerWidth, graphViewerHeight);

}
