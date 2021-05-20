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
    initializeTrashContainers("../data/trashContainers.txt");
    initializeGarbageFacilitys("../data/garbageFacilitys.txt");
    initializeCars("../data/cars.txt");
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
    fileHouses.close();
}

void Initializing::initializeTrashContainers(string filename) {
    ifstream fileTrashContainers(filename);
    int numberElements;
    fileTrashContainers>>numberElements;
    int id, maxCapacity;
    char trashType;
    char c1, c2,c3, c4;
    for(int i=0;i<numberElements;i++){
        fileTrashContainers>>c1>>id>>c2>>trashType>>c3>>maxCapacity>>c4;
        if(trashType=='G'){
            TrashContainer trashContainer(graph.findVertex(id), Glass, maxCapacity);
            trashContainers.push_back(trashContainer);
        }
        else if(trashType=='R'){
            TrashContainer trashContainer(graph.findVertex(id), Regular, maxCapacity);
            trashContainers.push_back(trashContainer);
        }
        else if(trashType=='P'){
            TrashContainer trashContainer(graph.findVertex(id), Paper, maxCapacity);
            trashContainers.push_back(trashContainer);
        }
        else if(trashType=='P'){
            TrashContainer trashContainer(graph.findVertex(id), Plastic, maxCapacity);
            trashContainers.push_back(trashContainer);
        }
    }
    fileTrashContainers.close();
}

void Initializing::initializeGarbageFacilitys(string filename) {
    ifstream fileGarbageFacilitys(filename);
    int numberElements;
    fileGarbageFacilitys >> numberElements;
    int id ;
    char c;
    string centralName;
    for(int i=0;i<numberElements;i++){
        fileGarbageFacilitys>>c>>id>>c>>centralName;
        centralName.pop_back();
        GarbageCollectionFacility garbageCollectionFacility(graph.findVertex(id), centralName);
        garbageCFs.push_back(garbageCollectionFacility);
    }
   fileGarbageFacilitys.close();
}

void Initializing::initializeCars(string filename) {
    ifstream fileCars(filename);
    int numberElements;
    fileCars >> numberElements;
    int capacity;
    string centralName;
    for(int i=0;i<numberElements;i++){
        fileCars>>capacity;
        Car car(capacity);
        cars.push_back(car);
    }
    fileCars.close();
}
