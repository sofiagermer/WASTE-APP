//
// Created by migue on 04/05/2021.
//

#ifndef WASTE_APP_DRIVER_H
#define WASTE_APP_DRIVER_H
#include "User.h"
#include "Car.h"

using namespace std;
class Driver: public User{
    /**
     * Amount of money earned by the Driver
     */
    double moneyEarned;

    /**
     * Pointer to the car the driver uses to pick up trash
     */
    Car *car;
public:
    Driver(int uId, Car *ca, string name, string password);

    Driver(int uID);

    Driver();

    void setMoneyEarned(double moneyEarned);

    double getMoneyEarned() const;

    Car *getCar() const;

    void setCar(Car *car);

    int getUserID();

    string getPassworD();

    //friend std::istream& operator>>(std::istream& input, Driver &d);

    /**
     * Output operator.
     */
    friend std::ostream& operator<<(std::ostream& output, const Driver &d);
};


#endif //WASTE_APP_DRIVER_H
