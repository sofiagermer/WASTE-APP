//
// Created by migue on 04/05/2021.
//

#include "GarbageCollectionFacility.h"

GarbageCollectionFacility::GarbageCollectionFacility(Vertex *vertexPt, string name) {
    this->vertexPt = vertexPt;
    this->name = name;
}

string GarbageCollectionFacility::getName() {
    return name;
}

Vertex *GarbageCollectionFacility::getVertex() {
    return this->vertexPt;
}
