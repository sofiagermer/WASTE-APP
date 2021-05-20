//
// Created by migue on 04/05/2021.
//

#include "Driver.h"

#include <utility>

Driver::Driver(int uID, Car *ca, string name, string password) : User(uID, move(name), move(password)), car(ca) {
    moneyEarned = 0;
}

Driver::Driver(int uID) : User(uID){
    moneyEarned = 0;
    car = nullptr;
}

Driver::Driver() : User(0) {
    moneyEarned = 0;
    car = nullptr;
}

Car *Driver::getCar() const {
    return car;
}

void Driver::setCar(Car *car) {
    Driver::car = car;
}

double Driver::getMoneyEarned() const {
    return moneyEarned;
}

void Driver::setMoneyEarned(double moneyEarned) {
    Driver::moneyEarned = moneyEarned;
}
