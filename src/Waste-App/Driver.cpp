//
// Created by migue on 04/05/2021.
//

#include "Driver.h"

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
