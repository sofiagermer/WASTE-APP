//
// Created by migue on 04/05/2021.
//

#include "Car.h"

Car::Car() {
    MaxCapacity = 0.0;
    CurrentCapacity = 0.0;
}

Car::Car(float maxcap): MaxCapacity(maxcap) {
    CurrentCapacity = 0;
}

float Car::getMaxCapacity() {
    return MaxCapacity;
}

float Car::getCurrentCapacity() {
    return CurrentCapacity;
}

void Car::setMaxcapacity(float maxcap) {
    MaxCapacity = maxcap;
}

void Car::setCurrentCapacity(float currentcap) {
    if(currentcap > MaxCapacity){
        throw TRASHWILLNOTFIT;
    }
    else {
        CurrentCapacity = currentcap;
    }
}

void Car::AddTrash(float amount) {
    if(CurrentCapacity + amount > MaxCapacity){
        throw TRASHWILLNOTFIT;
    }
    else {
        CurrentCapacity += amount;
    }
}
