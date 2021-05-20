//
// Created by migue on 04/05/2021.
//

#include "TrashContainer.h"

int TrashContainer::getMaxCapacity() const {
    return maxCapacity;
}

int TrashContainer::getCurrentCapacity() const {
    return currentCapacity;
}

TrashType TrashContainer::getType() const {
    return type;
}

TrashContainer::TrashContainer(Vertex *vertexPt, TrashType type ,int maxCapacity) {
    this->vertexPt = vertexPt;
    this->maxCapacity = maxCapacity;
    this->type = type;
    this->currentCapacity = maxCapacity;
}

Vertex *TrashContainer::getVertex() {
    return vertexPt;
}
