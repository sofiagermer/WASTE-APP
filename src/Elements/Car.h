//
// Created by migue on 04/05/2021.
//

#ifndef WASTE_APP_CAR_H
#define WASTE_APP_CAR_H

#include <iostream>
#include <string>
#include <ctime>

#define TRASHWILLNOTFIT "The trash amount is too high, the car cannot hold that much trash"

using namespace std;

class Car {
    float MaxCapacity;
    float CurrentCapacity;
    string LicensePlate;
public:
    /**
     * Default Constructor
     */
    Car();
    /**
     * Constructor
     * @param maxcap - the max capacity of the car
     */
    Car(float maxcap);
    /**
     *
     * @param maxcap
     * @param licenseplate
     */
    Car(float maxcap, string licenseplate);

    /**
     * Gets Maximum capacity of the car
     * @return Maximum capacity of the car
     */
    float getMaxCapacity();
    /**
     * Gets the current amount of the car thats filled with trash
     * @return Amount of trash in the car
     */
    float getCurrentCapacity();

    /**
     * Sets the amount of trash that the car can contain
     * @param maxcap - maximum amount of trash the car can contain
     */
    void setMaxcapacity(float maxcap);
    /**
     * Sets the current amount od trash inside the car
     * @throws TRASHWILLNOTFIT - if the trash amount surpasses that of the MaxCapacity defined for the car
     * @param currentcap - current amount of trash inside the car
     */
    void setCurrentCapacity(float currentcap);

    /**
     * Adds to the current car capacity an amount of trash
     * @throws TRASHWILLNOTFIT - if the trash amount will surpass that of the MaxCapacity defined for the car
     * @param amount - amount of trash to add to the car
     */
    bool addTrash(float amount);

    bool wouldFit(float amount){
        if(CurrentCapacity + amount > MaxCapacity){
            return false;
        }
        else {
            return true;
        }
    }

    /**
     *
     * @return
     */
    const string &getLicensePlate() const;

    void setLicensePlate(const string &licensePlate);
};


#endif //WASTE_APP_CAR_H
