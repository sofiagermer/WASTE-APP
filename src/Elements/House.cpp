//
// Created by migue on 04/05/2021.
//

#include "House.h"

House::House(Vertex *vertexPt, float amoutTrash, bool needPickUp) {
    this->needPickUp = needPickUp;
    this->vertexPt = vertexPt;
    this->amountTrash = amoutTrash;
}

House::House(Vertex *vertexPt, float amoutTrash) {
    this->vertexPt = vertexPt;
    this->amountTrash = amoutTrash;
    this->needPickUp = false;
}

House::House(Vertex *vertexPt) {
    this->vertexPt = vertexPt;
    this->amountTrash = 0;
    this->needPickUp = false;
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

void House::setNeedPickUp(bool needPickUp) {
    this->needPickUp=needPickUp;
}

bool House::getNeedPickUp() {
    return needPickUp;
}

int House::getHouseID() {
    return this->vertexPt->getID();
}

