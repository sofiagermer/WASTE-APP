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

TrashContainer::TrashContainer(int maxCapacity, TrashType type)
        : maxCapacity(maxCapacity), type(type) {
    this->currentCapacity=maxCapacity;
}
