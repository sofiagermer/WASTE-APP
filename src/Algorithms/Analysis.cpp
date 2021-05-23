//
// Created by sofia on 23/05/21.
//

#include <unistd.h>
#include "Analysis.h"
#include "Preprocessing.h"
#include "Routing.h"


void Analysis::preprocessingAnalysisTarjan() {
    cout<<endl<<"Using a Porto Map with 53 621 nodes."<<endl;

    //Initializes a full graph
    Graph graph("../Map/sccGiven/porto_strong_nodes_xy.txt","../Map/sccGiven/porto_strong_edges.txt");

    //Runs Tarjan's algorithm and records the time it took
    auto start = std::chrono::high_resolution_clock::now();
    Preprocessing::preprocessGraphTarjan(graph,"../Map/testNodes.txt","../Map/testEdges.txt");
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    //Reads the number of nodes created from the nodes file
    ifstream f("../Map/testNodes.txt");
    int nodes;
    f>>nodes;
    cout <<"Tarjan's Algorithm ran in "<<duration.count()<<" milliseconds and produced a graph with "<<nodes<<" nodes"<<endl;
    f.close();

    //Erases temporary files created to test the algorithm
    int result1=remove("../Map/testNodes.txt");
    int result2=remove("../Map/testEdges.txt");
    if(result1!=0 || result2!=0) cout <<"Error deleting temporary files"<<endl;
}

void Analysis::preprocessingAnalysisKosaraju() {
    cout<<endl<<"Using a Porto Map with 53 621 nodes."<<endl;

    //Initializes a full graph
    Graph graph("../Map/sccGiven/porto_strong_nodes_xy.txt","../Map/sccGiven/porto_strong_edges.txt");

    //Runs Kosaraju's algorithm and records the time it took
    auto start = std::chrono::high_resolution_clock::now();
    Preprocessing::preprocessGraphKosaraju(graph,"../Map/testNodes.txt","../Map/testEdges.txt");
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    //Reads the number of nodes created from the nodes file
    ifstream f("../Map/testNodes.txt");
    int nodes;
    f>>nodes;
    cout <<"Kosaraju's Algorithm ran in "<<duration.count()<<" milliseconds and produced a graph with "<<nodes<<" nodes"<<endl;
    f.close();

    //Erases temporary files created to test the algorithm
    int result1=remove("../Map/testNodes.txt");
    int result2=remove("../Map/testEdges.txt");
    if(result1!=0 || result2!=0) cout <<"Error deleting temporary files"<<endl;
}

void Analysis::aStarVsDijkstra(Graph graph) {
    srand (time(NULL));
    int index1=rand()%graph.getNumVertex();
    int index2=rand()%graph.getNumVertex();
    while(index1==index2) index2=rand()%graph.getNumVertex();
    auto v1 = graph.getVertexSet()[index1];
    auto v2 = graph.getVertexSet()[index2];
    auto start = std::chrono::high_resolution_clock::now();
    auto pathDijkstra=Routing::dijkstra(graph,v1,v2);
    auto end = std::chrono::high_resolution_clock::now();
    auto durationDijkstra = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    start = std::chrono::high_resolution_clock::now();
    auto pathAStar=Routing::aStar(graph,v1,v2);
    end = std::chrono::high_resolution_clock::now();
    auto durationAStar = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout<<endl<<"For the same 2 random points:"<<endl<<endl;
    cout<<"Dijkstra's algorithm took "<<durationDijkstra.count()<<" microseconds to compute the shortest path"<<endl;
    cout<<"A* algorithm took "<<durationAStar.count()<<" microseconds to compute the shortest path"<<endl<<endl;
    sleep(2);
}

void Analysis::dijkstraAnalysis(Graph graph) {
    srand (time(NULL));
    int index1=rand()%graph.getNumVertex();
    int index2=rand()%graph.getNumVertex();
    while(index1==index2) index2=rand()%graph.getNumVertex();
    auto v1 = graph.getVertexSet()[index1];
    auto v2 = graph.getVertexSet()[index2];
    auto start = std::chrono::high_resolution_clock::now();
    auto pathDijkstra=Routing::dijkstra(graph,v1,v2);
    auto end = std::chrono::high_resolution_clock::now();
    auto durationDijkstra = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout<<endl<<"Dijkstra's algorithm took "<<durationDijkstra.count()<<" microseconds to compute the shortest path between 2 random nodes"<<endl<<endl;
    sleep(2);
}


void Analysis::aStarAnalysis(Graph graph) {
    srand (time(NULL));
    int index1=rand()%graph.getNumVertex();
    int index2=rand()%graph.getNumVertex();
    while(index1==index2) index2=rand()%graph.getNumVertex();
    auto v1 = graph.getVertexSet()[index1];
    auto v2 = graph.getVertexSet()[index2];
    auto start = std::chrono::high_resolution_clock::now();
    auto pathAStar=Routing::aStar(graph,v1,v2);
    auto end = std::chrono::high_resolution_clock::now();
    auto durationAStar = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout<<endl<<"A* algorithm took "<<durationAStar.count()<<" microseconds to compute the shortest path between 2 random nodes"<<endl<<endl;
    sleep(2);
}