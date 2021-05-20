//
// Created by migue on 04/05/2021.
//

#ifndef WASTE_APP_HOUSE_H
#define WASTE_APP_HOUSE_H

#include <iostream>
#include <string>

#include "User.h"
#include "../Graph/Graph.h"


class House {
    float amountTrash;
    Vertex * vertexPt;

public:
    House(Vertex *vertexPt, float amountTrash);

    /**
     * Gets the user pointer
     * @return User pointer, to the user who lives in this house
     */

    bool getNeedPickUp();
    /**
     * Gets the Amount of trash that needs to be collected
     * @return Amount Of Trash to be collected
     */
    float getAmountOfTrash();

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

    Vertex* getHouseVertex();
};


#endif //WASTE_APP_HOUSE_H
