//
// Created by migue on 04/05/2021.
//

#ifndef WASTE_APP_DRIVER_H
#define WASTE_APP_DRIVER_H
#include "User.h"
#include "Car.h"

class Driver: public User{
private:
    /**
     * Amount of money earned by the Driver
     */
    double moneyEarned;

    /**
     * Pointer to the car the driver uses to pick up trash
     */
    Car *car;
public:
    void setMoneyEarned(double moneyEarned);

    double getMoneyEarned() const;

    Car *getCar() const;

    void setCar(Car *car);
};


#endif //WASTE_APP_DRIVER_H
