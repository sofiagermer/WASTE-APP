//
// Created by migue on 04/05/2021.
//

#ifndef WASTE_APP_GARBAGECOLLECTIONFACILITY_H
#define WASTE_APP_GARBAGECOLLECTIONFACILITY_H

#include <iostream>
#include "../Graph/Graph.h"

using namespace std;

class GarbageCollectionFacility{
private:
    /**
     * Name of the Garbage Collection Facility
     */
    string name;
    Vertex * vertexPt;
public:
    GarbageCollectionFacility(Vertex * vertexPt, string name);
    string getName();

    Vertex* getVertex();
};


#endif //WASTE_APP_GARBAGECOLLECTIONFACILITY_H
