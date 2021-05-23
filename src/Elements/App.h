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

class App {
    vector<House> houses;
    vector<TrashContainer> trashContainers;
    vector<GarbageCollectionFacility> garbageCFs;
    vector<Car> cars;
    Graph graph;
    vector<Driver> drivers;
    vector<User> users;

public:
    App();
    App(Graph graph);
    void initializePoints();
    void initializeHouses(string filename);
    void initializeTrashContainers(string filename);
    void initializeGarbageFacilities(string filename);
    void initializeCars(string filename);
    void initializeDrivers(string filename);
    void initializeUsers(string filename);

    void addCar(string licensePlate, float maxCarCap);
    Car* findCar(string licensePlate);
    int addUser(string name, string password);
    User* findUser(int userID, string password);
    int addDriver(string name, string password, string licensePlate);
    Driver* findDriver(int userID, string password);
    bool userIDRepeated(const int &userID);

    TrashContainer* findClosestTrashContainer(User user, TrashType type);

    //Algorithm's Analysis
    void preprocessingAnalysisTarjan();
    void preprocessingAnalysisKosaraju();
    void aStarAnalysis();
    void dijkstraAnalysis();
    void aStarVsDijkstra();
};



#endif //WASTE_APP_APP_H
