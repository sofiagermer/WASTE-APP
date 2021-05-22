//
// Created by migue on 04/05/2021.
//

#include "Car.h"

Car::Car() {
    MaxCapacity = 0.0;
    CurrentCapacity = 0.0;
    LicensePlate = "";
}

Car::Car(float maxcap): MaxCapacity(maxcap) {
    CurrentCapacity = 0;
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

void Car::AddTrash(float amount) {
    if(CurrentCapacity + amount > MaxCapacity){
        throw TRASHWILLNOTFIT;
    }
    else {
        CurrentCapacity += amount;
    }
}

const string &Car::getLicensePlate() const {
    return LicensePlate;
}

void Car::setLicensePlate(const string &licensePlate) {
    LicensePlate = licensePlate;
}
