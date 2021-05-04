//
// Created by migue on 04/05/2021.
//

#ifndef WASTE_APP_GARBAGECOLLECTIONFACILITY_H
#define WASTE_APP_GARBAGECOLLECTIONFACILITY_H

#include <iostream>

using namespace std;

class GarbageCollectionFacility {
private:

    /**
     * Name of the Garbage Collection Facility
     */
    string name;
public:
    const string &getName() const;


};


#endif //WASTE_APP_GARBAGECOLLECTIONFACILITY_H
