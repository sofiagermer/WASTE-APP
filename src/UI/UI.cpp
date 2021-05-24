//
// Created by sofia on 19/05/21.
//

#include "UI.h"

UI::UI(Graph * graph, int width, int height) : graph(graph), graphViewerHeight(graphViewerHeight), graphViewerWidth(graphViewerWidth){}

void UI::showGraph() {
    this->graphViewer = new GraphViewer();


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
    graphViewer->createWindow(graphViewerWidth, graphViewerHeight);
}

void UI::showTrashContainer(double userX, double userY, Vertex *trashContainer, TrashType type) {
    this->graphViewer = new GraphViewer();
    graphViewer->setCenter(sf::Vector2f(trashContainer->getX(), trashContainer->getY()));
    auto maxDist=graph->distanceBetweenCoords(userX,trashContainer->getX(),userY,trashContainer->getY());
    maxDist=maxDist*1.1;

    for (Vertex * vertex : graph->getVertexSet()) {
        if(graph->distanceBetweenCoords(userX,vertex->getX(),userY,vertex->getY())>maxDist) {
            continue;
        }
        graphViewer->addNode(vertex->getID(), sf::Vector2f (vertex->getX(), vertex->getY())).setColor(GraphViewer::DARK_GRAY);;

    }

    int id = 0;
    for (Vertex* vertex : graph->getVertexSet()) {
        if(graph->distanceBetweenCoords(userX,vertex->getX(),userY,vertex->getY())>maxDist)
            continue;
        for (Edge edge : vertex->getOutgoingEdges()) {
            if(graph->distanceBetweenCoords(edge.getDest()->getX(),userX,edge.getDest()->getY(),userY)>maxDist)
                continue;
            graphViewer->addEdge(id, graphViewer->getNode(vertex->getID()), graphViewer->getNode(edge.getDest()->getID()), GraphViewer::Edge::EdgeType::DIRECTED);
            id++;
        }
    }


    auto node=graphViewer->getNode(trashContainer->getID());
    switch (type) {
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
    auto userClosestNode= graph->findClosestVertex(userX,userY);
    auto graphViewerUserNode=graphViewer->getNode(userClosestNode->getID());
    graphViewerUserNode.setColor(GraphViewer::PINK);
    graphViewer->createWindow(graphViewerWidth, graphViewerHeight);
}
