//
// Created by sofia on 20/05/21.
//

#ifndef WASTE_APP_APP_H
#define WASTE_APP_APP_H


#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <string>
#include <fstream>
#include "House.h"
#include "TrashContainer.h"
#include "GarbageCollectionFacility.h"
#include "Car.h"
#include "../Algorithms/Preprocessing.h"
#include "../Algorithms/Routing.h"
#include "Driver.h"
#include "User.h"

class App {
    vector<House*> houses;
    vector<TrashContainer> trashContainers;
    vector<GarbageCollectionFacility> garbageCFs;
    vector<Car> cars;
    Graph *graph;
    vector<Driver> drivers;
    vector<User> users;

public:
    App();
    ~App(void);
    App(Graph *graph);
    void initializePoints();
    void initializeHouses(string filename);
    void initializeTrashContainers(string filename);
    void initializeGarbageFacilities(string filename);
    void initializeCars(string filename);
    void initializeDrivers(string filename);
    void initializeUsers(string filename);

    void saveInfo();
    void saveHouses(string filename);
    void saveTrashContainers(string filename);
    void saveGarbageFacilities(string filename);
    void saveCars(string filename);
    void saveDrivers(string filename);
    void saveUsers(string filename);

    House* findHouse(int houseid);
    void addCar(const string& licensePlate, float maxCarCap);
    Car* findCar(const string& licensePlate);
    int addUser(const string& name, const string& password);
    User* findUser(int userID, const string& password);
    int addDriver(const string& name, const string& password, const string& licensePlate);
    Driver* findDriver(int userID, const string& password);
    bool userIDRepeated(const int &userID);
    void setAdress(User *user);
    static double getX();
    static double getY();

    Vertex* findClosestTrashContainer(User user, TrashType type);

    //Algorithm's Analysis
    Graph* getGraph();

    vector<House *> getHousesToVisit();
};



#endif //WASTE_APP_APP_H
