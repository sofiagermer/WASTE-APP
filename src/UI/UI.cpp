//
// Created by sofia on 19/05/21.
//

#include "UI.h"

UI::UI(Graph * graph, int width, int height) : graph(graph), graphViewerHeight(graphViewerHeight), graphViewerWidth(graphViewerWidth){

}

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


    GraphViewer::Node &node=graphViewer->getNode(trashContainer->getID());
    switch (type) {
        case Paper:
            node.setColor(GraphViewer::BLUE);
            node.setSize(40);
            break;
        case Plastic:
            node.setColor(GraphViewer::YELLOW);
            node.setSize(40);
            break;
        case Glass:
            node.setColor(GraphViewer::GREEN);
            node.setSize(40);
            break;
        case Regular:
            node.setColor(GraphViewer::GRAY);
            node.setSize(40);
            break;
        default:
            break;
    }
    auto userClosestNode= graph->findClosestVertex(userX,userY);
    GraphViewer::Node &graphViewerUserNode=graphViewer->getNode(userClosestNode->getID());
    graphViewerUserNode.setColor(GraphViewer::PINK);
    graphViewerUserNode.setSize(40);
    graphViewer->createWindow(graphViewerWidth, graphViewerHeight);
}

void UI::displayRoute(vector<House *> houses, queue<Vertex *> route) {
    this->graphViewer = new GraphViewer();
    graphViewer->setCenter(sf::Vector2f(route.front()->getX(), route.front()->getY()));
    for (Vertex * vertex : graph->getVertexSet()) {
        GraphViewer::Node &n=graphViewer->addNode(vertex->getID(), sf::Vector2f (vertex->getX(), vertex->getY()));
        n.setColor(GraphViewer::LIGHT_GRAY);
        n.setSize(5);
    }
    while(!route.empty()){
        GraphViewer::Node &n = graphViewer->getNode(route.front()->getID());
        n.setColor(GraphViewer::YELLOW);
        n.setSize(10);
        for(auto h:houses){
            if(h->getHouseVertex()->getID()==route.front()->getID()){
                n.setSize(40);
                n.setColor(GraphViewer::GREEN);
                n.setOutlineColor(GraphViewer::RED);
                n.setLabel("HOUSE");
                break;
            }
        }
        route.pop();
    }
    int id = 0;
    for (Vertex* vertex : graph->getVertexSet()) {
        for (Edge edge : vertex->getOutgoingEdges()) {
            if((graphViewer->getNode(vertex->getID()).getColor()==GraphViewer::YELLOW || graphViewer->getNode(vertex->getID()).getColor()==GraphViewer::GREEN) && (graphViewer->getNode(edge.getDest()->getID()).getColor()==GraphViewer::YELLOW ||graphViewer->getNode(edge.getDest()->getID()).getColor()==GraphViewer::GREEN)){
                GraphViewer::Edge &edge1= graphViewer->addEdge(id, graphViewer->getNode(vertex->getID()), graphViewer->getNode(edge.getDest()->getID()), GraphViewer::Edge::EdgeType::DIRECTED);
                edge1.setColor(GraphViewer::BLUE);
                id++;
                continue;
            }
            graphViewer->addEdge(id, graphViewer->getNode(vertex->getID()), graphViewer->getNode(edge.getDest()->getID()), GraphViewer::Edge::EdgeType::DIRECTED);
            id++;
        }
    }
    graphViewer->createWindow(graphViewerWidth, graphViewerHeight);
}

void UI::displayTwoPointRoute(queue<Vertex *> route) {
    this->graphViewer = new GraphViewer();
    graphViewer->setCenter(sf::Vector2f(route.front()->getX(), route.front()->getY()));

    for (Vertex * vertex : graph->getVertexSet()) {
        GraphViewer::Node &n=graphViewer->addNode(vertex->getID(), sf::Vector2f (vertex->getX(), vertex->getY()));
        n.setColor(GraphViewer::LIGHT_GRAY);
        n.setSize(5);
    }
    auto front=route.front();
    auto back=route.back();
    while(!route.empty()){
        GraphViewer::Node &n = graphViewer->getNode(route.front()->getID());
        n.setColor(GraphViewer::YELLOW);
        n.setSize(10);
        if(n.getId()==front->getID()){
            n.setSize(40);
            n.setColor(GraphViewer::GREEN);
            n.setOutlineColor(GraphViewer::RED);
            n.setLabel("BEGIN");
        }
        else if(n.getId()==back->getID()){
                n.setSize(40);
                n.setColor(GraphViewer::GREEN);
                n.setOutlineColor(GraphViewer::RED);
                n.setLabel("END");
        }

        route.pop();
    }
    int id = 0;
    for (Vertex* vertex : graph->getVertexSet()) {
        for (Edge edge : vertex->getOutgoingEdges()) {
            if((graphViewer->getNode(vertex->getID()).getColor()==GraphViewer::YELLOW || graphViewer->getNode(vertex->getID()).getColor()==GraphViewer::GREEN) && (graphViewer->getNode(edge.getDest()->getID()).getColor()==GraphViewer::YELLOW ||graphViewer->getNode(edge.getDest()->getID()).getColor()==GraphViewer::GREEN)){
                GraphViewer::Edge &edge1= graphViewer->addEdge(id, graphViewer->getNode(vertex->getID()), graphViewer->getNode(edge.getDest()->getID()), GraphViewer::Edge::EdgeType::DIRECTED);
                edge1.setColor(GraphViewer::BLUE);
                id++;
                continue;
            }
            graphViewer->addEdge(id, graphViewer->getNode(vertex->getID()), graphViewer->getNode(edge.getDest()->getID()), GraphViewer::Edge::EdgeType::DIRECTED);
            id++;
        }
    }
    graphViewer->createWindow(graphViewerWidth, graphViewerHeight);
}
