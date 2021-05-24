//
// Created by migue on 04/05/2021.
//

#include "Car.h"

Car::Car(float maxcap): MaxCapacity(maxcap) {
    CurrentCapacity = maxcap;
    srand(time(NULL));
    for(int i = 0; i < 6; i++){
        LicensePlate.push_back((int) (rand() % 26 + 65));
    }
}

Car::Car(float maxcap, string licenseplate): MaxCapacity(maxcap), LicensePlate(licenseplate) {
    CurrentCapacity = maxcap;
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

bool Car::addTrash(float amount) {
    if(CurrentCapacity - amount < 0){
        return false;
    }
    else {
        CurrentCapacity -= amount;
        return true;
    }
}

const string &Car::getLicensePlate() const {
    return LicensePlate;
}

void Car::setLicensePlate(const string &licensePlate) {
    LicensePlate = licensePlate;
}

bool Car::wouldFit(float amount) {
    if(CurrentCapacity - amount < 0){
        return false;
    }
    else {
        return true;
    }
}
