//
// Created by migue on 04/05/2021.
//

#include "House.h"

House::House(Vertex *vertexPt, float amoutTrash) {
    this->vertexPt = vertexPt;
    this->amountTrash = amoutTrash;
}


float House::getAmountOfTrash() {
    return amountTrash;
}

void House::setAmountOfTrash(float amount) {
    amountTrash = amount;
}

Vertex* House::getHouseVertex(){
    return this->vertexPt;
}

