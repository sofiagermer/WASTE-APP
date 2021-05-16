//
// Created by migue on 04/05/2021.
//

#ifndef WASTE_APP_HOUSE_H
#define WASTE_APP_HOUSE_H

#include <iostream>
#include <string>

#include "User.h"



class House {
    User* UserPt;
    bool NeedPickUp;
    float AmountOfTrash;

public:
    /**
     * Default constructor
     */
    House();
    /**
     * Constructor
     * @param up - User pointer, to the user who lives in this house
     */
    House(User* up);

    /**
     * Gets the user pointer
     * @return User pointer, to the user who lives in this house
     */
    User* getUserPt();
    /**
     * Gets the flag if the house has trash that needs to be picked up
     * @return Need Pick Up falg
     */
    bool getNeedPickUp();
    /**
     * Gets the Amount of trash that needs to be collected
     * @return Amount Of Trash to be collected
     */
    float getAmountOfTrash();

    /**
     * Sets the User pointer
     * @param up - User pointer to set
     */
    void setUserPt(User* up);
    /**
     * Sets the flag if the house needs trash to be collected
     * @param needpu - flag if the house needs collection
     */
    void setNeedPickUp(bool needpu);
    /**
     * Sets the amount of trash that the house needs coleected
     * @param amount - amount of trash to collect
     */
    void setAmountOfTrash(float amount);

};


#endif //WASTE_APP_HOUSE_H
