//
// Created by migue on 04/05/2021.
//

#ifndef WASTE_APP_TRASHCONTAINER_H
#define WASTE_APP_TRASHCONTAINER_H

enum TrashType {Regular,Paper,Plastic,Glass};

class TrashContainer{
private:
    /**
     * Maximum Capacity - the maximum amount of waste it can hold
     */
    int maxCapacity;

    /**
     * Current Capacity - the current amount of trash the container has, given by sensors in the container
     */
    int currentCapacity;

    /**
     * Type of trash the container takes - Can be Regular, Paper, Plastic or Glass
     */
    TrashType type;
public:

    TrashContainer(int maxCapacity, TrashType type);

    int getMaxCapacity() const;

    int getCurrentCapacity() const;

    TrashType getType() const;
};


#endif //WASTE_APP_TRASHCONTAINER_H
