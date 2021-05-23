//
// Created by sofia on 20/05/21.
//


#include "App.h"

using namespace std;

App::App() {}

App::App(Graph graph) {
    this->graph = graph;
    initializePoints();
}

void App::initializePoints(){
    initializeHouses("../data/houses.txt");
    initializeTrashContainers("../data/trashContainers.txt");
    initializeGarbageFacilities("../data/garbageFacilitys.txt");
    initializeCars("../data/cars.txt");
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
        else if(trashType=='P'){
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
    int capacity;
    string centralName;
    for(int i=0;i<numberElements;i++){
        fileCars>>capacity;
        Car car(capacity);
        cars.push_back(car);
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
        User u;
        fileUsers >> u;
        users.push_back(u);
    }
    fileUsers.close();
}

void App::addCar(string licensePlate, float maxCarCap) {
    cars.emplace_back(maxCarCap, licensePlate);
}

Car *App::findCar(string licensePlate) {
    for(auto carit = cars.begin(); carit < cars.end(); carit++){
        if((*carit).getLicensePlate() == licensePlate) return &(*carit);
    }
    return nullptr;
}

bool App::userIDRepeated(const int &userid) {
    for(auto u : users) if(u.getUserId() == userid) return true;
    for(auto d : drivers) if(d.getUserId() == userid) return true;
    return false;
}

int App::addUser(string name, string password) {
    srand(time(NULL));
    int userid = rand();
    while (userIDRepeated(userid)) userid = rand();
    users.emplace_back(userid, name, password);
    return userid;
}

User *App::findUser(int userID, string password) {
    for(auto userit = users.begin(); userit < users.end(); userit++){
        if((*userit).getUserId() == userID && (*userit).getPassword() == password) return &(*userit);
    }
    return nullptr;
}

int App::addDriver(string name, string password, string licensePlate) {
    srand(time(NULL));
    int userid = rand();
    while (userIDRepeated(userid)) userid = rand();
    Car* car = findCar(licensePlate);
    if(car == nullptr) return -1;
    drivers.emplace_back(userid, car, name, password);
    return userid;
}

Driver *App::findDriver(int userID, string password) {
    for(auto driverit = drivers.begin(); driverit < drivers.end(); driverit++){
        if((*driverit).getUserId() == userID && (*driverit).getPassword() == password) return &(*driverit);
    }
    return nullptr;
}



void App::preprocessingAnalysisTarjan() {
    cout<<endl<<"Using a Porto Map with 53 621 nodes."<<endl;

    //Initializes a full graph
    Graph graph("../Map/porto_full_nodes_xy.txt","../Map/porto_full_edges.txt");

    //Runs Tarjan's algorithm and records the time it took
    auto start = std::chrono::high_resolution_clock::now();
    Preprocessing::preprocessGraphTarjan(graph,"../Map/testNodes.txt","../Map/testEdges.txt");
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    //Reads the number of nodes created from the nodes file
    ifstream f("../Map/testNodes.txt");
    int nodes;
    f>>nodes;
    cout <<"Tarjan's Algorithm ran in "<<duration.count()<<" milliseconds and produced a graph with "<<nodes<<" nodes"<<endl;
    f.close();

    //Erases temporary files created to test the algorithm
    int result1=remove("../Map/testNodes.txt");
    int result2=remove("../Map/testEdges.txt");
    if(result1!=0 || result2!=0) cout <<"Error deleting temporary files"<<endl;
}

void App::preprocessingAnalysisKosaraju() {
    cout<<endl<<"Using a Porto Map with 53 621 nodes."<<endl;

    //Initializes a full graph
    Graph graph("../Map/porto_full_nodes_xy.txt","../Map/porto_full_edges.txt");

    //Runs Kosaraju's algorithm and records the time it took
    auto start = std::chrono::high_resolution_clock::now();
    Preprocessing::preprocessGraphKosaraju(graph,"../Map/testNodes.txt","../Map/testEdges.txt");
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    //Reads the number of nodes created from the nodes file
    ifstream f("../Map/testNodes.txt");
    int nodes;
    f>>nodes;
    cout <<"Kosaraju's Algorithm ran in "<<duration.count()<<" milliseconds and produced a graph with "<<nodes<<" nodes"<<endl;
    f.close();

    //Erases temporary files created to test the algorithm
    int result1=remove("../Map/testNodes.txt");
    int result2=remove("../Map/testEdges.txt");
    if(result1!=0 || result2!=0) cout <<"Error deleting temporary files"<<endl;
}

void App::aStarAnalysis() {
    srand (time(NULL));
    int index1=rand()%graph.getNumVertex();
    int index2=rand()%graph.getNumVertex();
    while(index1==index2) index2=rand()%graph.getNumVertex();
    auto v1 = graph.getVertexSet()[index1];
    auto v2 = graph.getVertexSet()[index2];
    auto start = std::chrono::high_resolution_clock::now();
    auto pathAStar=Routing::aStar(graph,v1,v2);
    auto end = std::chrono::high_resolution_clock::now();
    auto durationAStar = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout<<endl<<"A* algorithm took "<<durationAStar.count()<<" microseconds to compute the shortest path between 2 random nodes"<<endl<<endl;
    sleep(2);
}

TrashContainer* App::findClosestTrashContainer(User user, TrashType type) {
    auto userLocation=graph.findClosestVertex(user.getX(),user.getY());
    TrashContainer* selectedTrashContainer= nullptr;
    double min=INF;
    for(auto t:trashContainers){
        if(t.getType()==type && t.getCurrentCapacity()>0){
            auto temp=Routing::dijkstra(graph,userLocation,t.getVertex());
            if(Routing::pathCost(temp)<min){
                selectedTrashContainer=&t;
            }
        }
    }
    return selectedTrashContainer;
}

void App::aStarVsDijkstra() {
    srand (time(NULL));
    int index1=rand()%graph.getNumVertex();
    int index2=rand()%graph.getNumVertex();
    while(index1==index2) index2=rand()%graph.getNumVertex();
    auto v1 = graph.getVertexSet()[index1];
    auto v2 = graph.getVertexSet()[index2];
    auto start = std::chrono::high_resolution_clock::now();
    auto pathDijkstra=Routing::dijkstra(graph,v1,v2);
    auto end = std::chrono::high_resolution_clock::now();
    auto durationDijkstra = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    start = std::chrono::high_resolution_clock::now();
    auto pathAStar=Routing::aStar(graph,v1,v2);
    end = std::chrono::high_resolution_clock::now();
    auto durationAStar = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout<<endl<<"For the same 2 random points:"<<endl<<endl;
    cout<<"Dijkstra's algorithm took "<<durationDijkstra.count()<<" microseconds to compute the shortest path"<<endl;
    cout<<"A* algorithm took "<<durationAStar.count()<<" microseconds to compute the shortest path"<<endl<<endl;
    sleep(2);
}

void App::dijkstraAnalysis() {
    srand (time(NULL));
    int index1=rand()%graph.getNumVertex();
    int index2=rand()%graph.getNumVertex();
    while(index1==index2) index2=rand()%graph.getNumVertex();
    auto v1 = graph.getVertexSet()[index1];
    auto v2 = graph.getVertexSet()[index2];
    auto start = std::chrono::high_resolution_clock::now();
    auto pathDijkstra=Routing::dijkstra(graph,v1,v2);
    auto end = std::chrono::high_resolution_clock::now();
    auto durationDijkstra = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout<<endl<<"Dijkstra's algorithm took "<<durationDijkstra.count()<<" microseconds to compute the shortest path between 2 random nodes"<<endl<<endl;
    sleep(2);
}

