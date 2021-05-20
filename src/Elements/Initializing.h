//
// Created by sofia on 20/05/21.
//

#ifndef WASTE_APP_INITIALIZING_H
#define WASTE_APP_INITIALIZING_H


#include "House.h"
#include "TrashContainer.h"
#include "GarbageCollectionFacility.h"
#include "Car.h"

class Initializing {
    vector<House> houses;
    vector<TrashContainer> trashContainers;
    vector<GarbageCollectionFacility> garbageCFs;
    vector<Car> cars;
    Graph graph;

public:
    Initializing(Graph graph);
    void initializePoints();
    void initializeHouses(string filename);
    void initializeTrashContainers(string filename);
    void initializeGarbageFacilitys(string filename);
    void initializeCars(string filename);
};


#endif //WASTE_APP_INITIALIZING_H
