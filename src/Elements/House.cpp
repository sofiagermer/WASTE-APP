//
// Created by migue on 04/05/2021.
//

#include "House.h"

House::House() {
    UserPt = NULL;
    NeedPickUp = false;
    AmountOfTrash = 0.0;
}

House::House(User* up): UserPt(up) {
    NeedPickUp = false;
    AmountOfTrash = 0.0;
}

User * House::getUserPt() {
    return UserPt;
}

bool House::getNeedPickUp() {
    return NeedPickUp;
}

float House::getAmountOfTrash() {
    return AmountOfTrash;
}

void House::setUserPt(User *up) {
    UserPt = up;
}

void House::setNeedPickUp(bool needpu) {
    NeedPickUp = needpu;
}

void House::setAmountOfTrash(float amount) {
    AmountOfTrash = amount;
}

