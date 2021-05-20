//
// Created by sofia on 20/05/21.
//

#include <iostream>
#include <string>
#include <fstream>
#include "Initializing.h"

using namespace std;

Initializing::Initializing(Graph graph) {
    this->graph = graph;
    initializePoints();
}

void Initializing::initializePoints(){
    initializeHouses("../data/houses.txt");
    //initializeTrashContainers("../data/trashContainers.txt");
    //initializeGarbageFacilitys("../data/garbageFacilitys.txt");
}

void Initializing::initializeHouses(string filename) {
    ifstream fileHouses(filename);
    int numberElements;
    fileHouses>>numberElements;
    int id;
    float amountTrash;
    char c;
    for(int i=0;i<numberElements;i++){
        fileHouses>>c>>id>>c>>amountTrash>>c;
        House house(graph.findVertex(id),amountTrash);
        houses.push_back(house);
    }
}

/*
void Initializing::initializeTrashContainers(string filename) {
    ifstream fileTrashContainers(filename);
    int numberElements;
    fileTrashContainers>>numberElements;
    int id, x, y;
    for(int i=0;i<numberElements;i++){
        fileTrashContainers>>id>>x>>y;
    }
}

void Initializing::initializeGarbageFacilitys(string filename) {
    ifstream fileGarbageFacilitys(filename);
    int numberElements;
    fileGarbageFacilitys >> numberElements;
    int id, x, y;
    for(int i=0;i<numberElements;i++){
        fileGarbageFacilitys>>id>>x>>y;
    }
}*/