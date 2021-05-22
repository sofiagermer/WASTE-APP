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

//NEED SOME CHANGES!!!
void App::initializeDrivers(string filename) {
    ifstream fileDrivers(filename);
    int numDrivers;
    fileDrivers >> numDrivers;
    for(int i = 0; i < numDrivers; i++){
        Driver d(0);
        fileDrivers >> d;
        drivers.push_back(d);
    }
    fileDrivers.close();
}

void App::initializeUsers(string filename){
    ifstream fileUsers(filename);
    int numUsers;
    fileUsers >> numUsers;
    for(int i = 0; i < numUsers; i++){
        User u(0);
        fileUsers >> u;
        users.push_back(u);
    }
    fileUsers.close();
}


void App::preprocessingAnalysisTarjan() {
    cout<<endl<<"Using a Porto Map with 53 621 nodes."<<endl;

    //Initializes a full graph
    Graph graph("../Map/porto_full_nodes_xy.txt","../Map/porto_full_edges.txt");

    //Runs Tarjan's algorithm and records the time it took
    auto start = std::chrono::high_resolution_clock::now();
    (graph,"../Map/testNodes.txt","../Map/testEdges.txt");
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

void App::aStarAnalysis() {
    auto v1 = graph.findVertex(3);
    auto v2 = graph.findVertex(8);

    auto start = std::chrono::high_resolution_clock::now();
    auto pathAStar=Routing::aStar(graph,v1,v2);
    auto end = std::chrono::high_resolution_clock::now();
    auto durationAStar = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout<<"A:"<<durationAStar.count()<<endl;
    start = std::chrono::high_resolution_clock::now();
    auto pathDijkstra=Routing::dijkstra(graph,v1,v2);
    end = std::chrono::high_resolution_clock::now();
    auto durationDijkstra = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    cout<<"D:"<<durationDijkstra.count()<<endl;
}

void App::addCar(string licenseplate, float maxcarcap) {

}

Car *App::findCar(string licenseplate) {
    return nullptr;
}

int App::addUser(string name, string password) {
    return 0;
}

User *App::findUser(int userID, string password) {
    return nullptr;
}

int App::addDriver(string name, string password, string licenseplate) {
    return 0;
}

Driver *App::findDriver(int userID, string password) {
    return nullptr;
}
