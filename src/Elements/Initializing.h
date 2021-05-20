//
// Created by sofia on 20/05/21.
//

#ifndef WASTE_APP_INITIALIZING_H
#define WASTE_APP_INITIALIZING_H


#include "House.h"
#include "TrashContainer.h"
#include "GarbageCollectionFacility.h"

class Initializing {
    vector<House> houses;
    vector<TrashContainer> trashContainers;
    vector<GarbageCollectionFacility> garbageCFs;
    Graph graph;

public:
    Initializing(Graph graph);
    void initializeHouses(string filename);
    void initializeTrashContainers(string filename);
    void initializeGarbageFacilitys(string filename);
    void initializePoints();

    Initializing(Graph *pGraph);
};


#endif //WASTE_APP_INITIALIZING_H
