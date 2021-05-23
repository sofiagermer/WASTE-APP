//
// Created by sofia on 20/05/21.
//


#include "App.h"

using namespace std;

App::App() = default;

App::App(Graph graph) {
    this->graph = graph;
    initializePoints();
}

void App::initializePoints(){
    initializeHouses("../data/houses.txt");
    initializeTrashContainers("../data/trashContainers.txt");
    initializeGarbageFacilities("../data/garbageFacilitys.txt");
    initializeCars("../data/cars.txt");
    initializeDrivers("../data/drivers.txt");
    initializeUsers("../data/users.txt");
}

void App::initializeHouses(string filename) {
    ifstream fileHouses(filename);
    int numberElements;
    fileHouses>>numberElements;
    int id;
    float amountTrash;
    char c;
    for(int i=0;i<numberElements;i++){
        fileHouses>>c>>id>>c>>amountTrash>>c;
        House house(graph.findVertex(id),amountTrash);
        houses.push_back(house);
    }
    fileHouses.close();
}

void App::initializeTrashContainers(string filename) {
    ifstream fileTrashContainers(filename);
    int numberElements;
    fileTrashContainers>>numberElements;
    int id, maxCapacity;
    char trashType;
    char c1, c2,c3, c4;
    for(int i=0;i<numberElements;i++){
        fileTrashContainers>>c1>>id>>c2>>trashType>>c3>>maxCapacity>>c4;
        if(trashType=='G'){
            TrashContainer trashContainer(graph.findVertex(id), Glass, maxCapacity);
            trashContainers.push_back(trashContainer);
        }
        else if(trashType=='R'){
            TrashContainer trashContainer(graph.findVertex(id), Regular, maxCapacity);
            trashContainers.push_back(trashContainer);
        }
        else if(trashType=='p'){
            TrashContainer trashContainer(graph.findVertex(id), Paper, maxCapacity);
            trashContainers.push_back(trashContainer);
        }
        else if(trashType=='P'){
            TrashContainer trashContainer(graph.findVertex(id), Plastic, maxCapacity);
            trashContainers.push_back(trashContainer);
        }
    }
    fileTrashContainers.close();
}

void App::initializeGarbageFacilities(string filename) {
    ifstream fileGarbageFacilitys(filename);
    int numberElements;
    fileGarbageFacilitys >> numberElements;
    int id ;
    char c;
    string centralName;
    for(int i=0;i<numberElements;i++){
        fileGarbageFacilitys>>c>>id>>c>>centralName;
        centralName.pop_back();
        GarbageCollectionFacility garbageCollectionFacility(graph.findVertex(id), centralName);
        garbageCFs.push_back(garbageCollectionFacility);
    }
   fileGarbageFacilitys.close();
}

void App::initializeCars(string filename) {
    ifstream fileCars(filename);
    int numberElements;
    fileCars >> numberElements;
    float capacity;
    string licenseplate;
    for(int i=0;i<numberElements;i++){
        fileCars >> capacity >> licenseplate;
        cars.emplace_back(capacity, licenseplate);
    }
    fileCars.close();
}

void App::initializeDrivers(string filename) {
    ifstream fileDrivers(filename);
    int numDrivers;
    fileDrivers >> numDrivers;
    for(int i = 0; i < numDrivers; i++){
        std::string uname, upassword, carlicenseplate;
        int uid;
        float carmaxcap, moneyearned;
        fileDrivers >> uid >> uname >> upassword >> moneyearned >> carlicenseplate >> carmaxcap;
        Car* car = findCar(carlicenseplate);
        if(car == nullptr) {
            addCar(carlicenseplate, carmaxcap);
            car = findCar(carlicenseplate);
        }
        Driver driver(uid, car, uname, upassword);
        driver.setMoneyEarned(moneyearned);
        drivers.push_back(driver);
    }
    fileDrivers.close();
}

void App::initializeUsers(string filename){
    ifstream fileUsers(filename);
    int numUsers;
    fileUsers >> numUsers;
    for(int i = 0; i < numUsers; i++){
        string username, userpassword;
        int userid, houseid;
        fileUsers >> userid >> username >> userpassword >> houseid;
        User u(userid, username, userpassword);
        House* house = findHouse(graph.findVertex(houseid));
        if(house == nullptr) {
            houses.emplace_back(graph.findVertex(houseid), 0);
            house = findHouse(graph.findVertex(houseid));
        }
        u.setHouse(house);
        users.push_back(u);
    }
    fileUsers.close();
}

void App::addCar(const string& licensePlate, float maxCarCap) {
    cars.emplace_back(maxCarCap, licensePlate);
}

Car *App::findCar(const string& licensePlate) {
    for(auto carit = cars.begin(); carit < cars.end(); carit++){
        if((*carit).getLicensePlate() == licensePlate) return &(*carit);
    }
    return nullptr;
}

House *App::findHouse(Vertex* housevertex) {
    for(auto houseit = houses.begin(); houseit < houses.end(); houseit++){
        if((*houseit).getHouseVertex()->getID() == housevertex->getID()) return &(*houseit);
    }
    return nullptr;
}

bool App::userIDRepeated(const int &userid) {
    for(const auto& u : users) if(u.getUserId() == userid) return true;
    for(auto& d : drivers) if(d.getUserID() == userid) return true;
    return false;
}

int App::addUser(const string& name, const string& password) {
    srand(time(nullptr));
    int userid = rand();
    while (userIDRepeated(userid)) userid = rand();
    users.emplace_back(userid, name, password);
    return userid;
}

User *App::findUser(int userID, const string& password) {
    for(auto userit = users.begin(); userit < users.end(); userit++){
        if((*userit).getUserId() == userID && (*userit).getPassword() == password) return &(*userit);
    }
    return nullptr;
}

int App::addDriver(const string& name, const string& password, const string& licensePlate) {
    srand(time(NULL));
    int userid = rand();
    while (userIDRepeated(userid)) userid = rand();
    Car* car = findCar(licensePlate);
    if(car == nullptr) return -1;
    drivers.emplace_back(userid, car, name, password);
    return userid;
}

Driver *App::findDriver(int userID, const string& password) {
    for(auto driverit = drivers.begin(); driverit < drivers.end(); driverit++){
        if((*driverit).getUserID() == userID && (*driverit).getPassworD() == password) return &(*driverit);
    }
    return nullptr;
}

TrashContainer* App::findClosestTrashContainer(User user, TrashType type) {
    cout << "aqui " << endl;
    auto userLocation=graph.findClosestVertex(user.getX(),user.getY());
    TrashContainer* selectedTrashContainer= nullptr;
    double min=INF;
    cout << "antes do for " << endl;
    for(auto t:trashContainers){
        cout << "dentro do for " << endl;
        if(t.getType()==type && t.getCurrentCapacity()>0){
            cout << "disjktra merdou" << endl;
            auto temp=Routing::dijkstra(graph,userLocation,t.getVertex());
            cout << "NAO SE CHMA DISKSTRASSSSSS " << endl;
            if(Routing::pathCost(temp)<min){
                selectedTrashContainer=&t;
            }
        }
    }
    cout << "depois do for" << endl;
    return selectedTrashContainer;
}

Graph App::getGraph(){
    return graph;
}

void App::saveInfo(){
    saveHouses("../data/houses.txt");
    saveTrashContainers("../data/trashContainers.txt");
    saveGarbageFacilities("../data/garbageFacilitys.txt");
    saveCars("../data/cars.txt");
    saveDrivers("../data/drivers.txt");
    saveUsers("../data/users.txt");
}
void App::saveHouses(string filename){
    ofstream fileHouses(filename);
    fileHouses << houses.size() << "\n";
    for(auto h : houses){
        fileHouses << h.getHouseVertex()->getID() << " " << h.getAmountOfTrash() << "\n";
    }
    fileHouses.close();
}
void App::saveTrashContainers(string filename){
    ofstream fileTrashContainers(filename);
    fileTrashContainers << trashContainers.size() << "\n";
    for (auto tc : trashContainers){
        switch (tc.getType()) {
            case Regular:
                fileTrashContainers << tc.getVertex()->getID() << " " << 'R' << " " << tc.getMaxCapacity() << "\n";
                break;

            case Paper:
                fileTrashContainers << tc.getVertex()->getID() << " " << 'p' << " " << tc.getMaxCapacity() << "\n";
                break;
            case Plastic:
                fileTrashContainers << tc.getVertex()->getID() << " " << 'P' << " " << tc.getMaxCapacity() << "\n";

                break;
            case Glass:
                fileTrashContainers << tc.getVertex()->getID() << " " << 'G' << " " << tc.getMaxCapacity() << "\n";
                break;
        }
    }
    fileTrashContainers.close();
}
void App::saveGarbageFacilities(string filename){
    ofstream fileGarbageFacilitys(filename);
    fileGarbageFacilitys << garbageCFs.size() << endl;
    for(auto gf : garbageCFs){
        fileGarbageFacilitys << gf.getVertex()->getID() << " " << gf.getName() << endl;
    }
    fileGarbageFacilitys.close();
}
void App::saveCars(string filename){
    ofstream fileCars(filename);
    fileCars << cars.size() << endl;
    for(auto c: cars){
        fileCars << c.getMaxCapacity() << " " << c.getLicensePlate() << endl;
    }
    fileCars.close();
}
void App::saveDrivers(string filename){
    ofstream fileDrivers(filename);
    fileDrivers << drivers.size() << "\n";
    for(const auto& d: drivers) fileDrivers << d;
    fileDrivers.close();
}
void App::saveUsers(string filename){
    ofstream fileUsers(filename);
    fileUsers << drivers.size() << "\n";
    for(const auto& u: users) fileUsers << u;
    fileUsers.close();
}
