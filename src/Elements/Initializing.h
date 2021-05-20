//
// Created by sofia on 20/05/21.
//

#ifndef WASTE_APP_INITIALIZING_H
#define WASTE_APP_INITIALIZING_H


#include "House.h"

class Initializing {
    vector<House> houses;
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
