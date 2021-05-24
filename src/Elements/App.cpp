//
// Created by sofia on 20/05/21.
//


#include "App.h"

using namespace std;

App::App() = default;

App::App(Graph *graph) {
    this->graph = graph;
    initializePoints();
}

App::~App(){
    /*for(auto h: houses){
        delete h;
    }
    houses.clear();*/
};

/* ================================================================================================
 * READ FROM FILES
 * ================================================================================================
 */
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
    int needPickUp;
    char c;
    for(int i=0;i<numberElements;i++){
        fileHouses>>c>>id>>c>>amountTrash>>c>>needPickUp>>c;
        houses.push_back(new House(graph->findVertex(id),amountTrash,needPickUp));
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
            TrashContainer trashContainer(graph->findVertex(id), Glass, maxCapacity);
            trashContainers.push_back(trashContainer);
        }
        else if(trashType=='R'){
            TrashContainer trashContainer(graph->findVertex(id), Regular, maxCapacity);
            trashContainers.push_back(trashContainer);
        }
        else if(trashType=='p'){
            TrashContainer trashContainer(graph->findVertex(id), Paper, maxCapacity);
            trashContainers.push_back(trashContainer);
        }
        else if(trashType=='P'){
            TrashContainer trashContainer(graph->findVertex(id), Plastic, maxCapacity);
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
        garbageCFs.push_back(new GarbageCollectionFacility(graph->findVertex(id), centralName));
    }
   fileGarbageFacilitys.close();
}

void App::initializeCars(string filename) {
    ifstream fileCars(filename);
    int numberElements;
    char c;
    fileCars >> numberElements;
    float capacity;
    string licenseplate;
    for(int i=0;i<numberElements;i++){
        fileCars >> c >>capacity >> c >> licenseplate;
        licenseplate.pop_back();
        cars.emplace_back(capacity, licenseplate);
    }
    fileCars.close();
}

void App::initializeDrivers(string filename) {
    string uname, upassword, carlicenseplate;
    string bigString;
    int uid;
    float carmaxcap, moneyearned;
    ifstream fileDrivers(filename);
    int numDrivers;
    char c;
    fileDrivers >> numDrivers;
    for(int i = 0; i < numDrivers; i++){
        fileDrivers >> c >> uid >> c >> moneyearned >> c >>carmaxcap>> c >> bigString;
        ////Drivers name
        size_t pos = bigString.find(',');
        uname = bigString.substr(0,pos);
        bigString.erase(0, pos + 1);
        ////Drivers password
        pos = bigString.find(',');
        upassword = bigString.substr(0,pos);
        ////Cars Licence plate
        bigString.erase(0, pos + 1);
        bigString.pop_back();
        carlicenseplate = bigString;
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
    string username, userpassword;
    string bigString;
    int numUsers;
    fileUsers >> numUsers;
    char c;
    for(int i = 0; i < numUsers; i++){
        int userid, houseid;
        fileUsers >> c >> userid >> c >> houseid >> c >> bigString;
        ////Name
        size_t pos = bigString.find(',');
        username = bigString.substr(0,pos);
        bigString.erase(0, pos + 1);
        ////Password
        pos = bigString.find(',');
        bigString.pop_back();
        userpassword = bigString.substr(0,pos);
        bigString.erase(0, pos + 1);

        User u(userid, username, userpassword);
        House* house = findHouse(houseid);
        if(house != nullptr){
            houses.push_back(house);
            u.setHouse(house);
        }
        users.push_back(u);
    }
    fileUsers.close();
}

/* ================================================================================================
 * WRITE TO FILES
 * ================================================================================================
 */

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
    for(House * h : houses){
        fileHouses << '(' << h->getHouseVertex()->getID() << ',' << h->getAmountOfTrash() << ',' << h->getNeedPickUp() << ')' << "\n";
    }
    fileHouses.close();

}

void App::saveTrashContainers(string filename){
    ofstream fileTrashContainers(filename);
    fileTrashContainers << trashContainers.size() << "\n";
    for (auto tc : trashContainers){
        switch (tc.getType()) {
            case Regular:
                fileTrashContainers << '(' << tc.getVertex()->getID() << ',' << 'R' << ','<< tc.getMaxCapacity() << ')' << "\n";
                break;

            case Paper:
                fileTrashContainers << '(' << tc.getVertex()->getID() << ',' << 'p' << ',' << tc.getMaxCapacity() << ')' << "\n";
                break;
            case Plastic:
                fileTrashContainers << '(' <<  tc.getVertex()->getID() << ','<< 'P' <<',' << tc.getMaxCapacity() << ')' <<  "\n";

                break;
            case Glass:
                fileTrashContainers << '(' << tc.getVertex()->getID() << ',' << 'G' << ',' << tc.getMaxCapacity() << ')' << "\n";
                break;
        }
    }
    fileTrashContainers.close();
}

void App::saveGarbageFacilities(string filename){
    ofstream fileGarbageFacilitys(filename);
    fileGarbageFacilitys << garbageCFs.size() << endl;
    for(GarbageCollectionFacility* gf : garbageCFs){
        fileGarbageFacilitys << '('  << gf->getVertex()->getID() << ',' << gf->getName() << ')' << "\n";
    }
    fileGarbageFacilitys.close();
}

void App::saveCars(string filename){
    ofstream fileCars(filename);
    fileCars << cars.size() << endl;
    for(Car c: cars){
        fileCars << '(' << c.getMaxCapacity() << ',' << c.getLicensePlate() << ')'<< "\n";
    }
    fileCars.close();
}

void App::saveDrivers(string filename){
    ofstream fileDrivers(filename);
    fileDrivers << drivers.size() << "\n";
    for(Driver d: drivers) {
        fileDrivers << '('<< d.getUserId() << ',' << d.getMoneyEarned() <<',' << d.getCar()->getMaxCapacity() <<',' << d.getName() << ',' << d.getPassword()  << ',' << d.getCar()->getLicensePlate()  << ')' << "\n";
    }
    fileDrivers.close();
}

void App::saveUsers(string filename){
    ofstream fileUsers(filename);
    fileUsers << users.size() << "\n";
    for(User u: users) {
        if(u.getHouse() == nullptr) {
            fileUsers << '(' << u.getUserId() << ',' << -1 << ',' << u.getName() << ',' << u.getPassword() << ')' << "\n";
        }
        else{
            fileUsers << '(' << u.getUserId() << ',' << u.getHouse()->getHouseID() << ',' << u.getName() << ',' << u.getPassword() << ')' << "\n";
        }
    }
    fileUsers.close();
}

/* ================================================================================================
 * APP FUNCTIONS
 * ================================================================================================
 */
void App::addCar(const string& licensePlate, float maxCarCap) {
    cars.emplace_back(maxCarCap, licensePlate);
}

Car *App::findCar(const string& licensePlate) {
    for(auto carit = cars.begin(); carit < cars.end(); carit++){
        if((*carit).getLicensePlate() == licensePlate) return &(*carit);
    }
    return nullptr;
}

House *App::findHouse(int houseid) {
    for(House *house :houses){
        if(house->getHouseVertex()->getID() == houseid) return house;
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

Vertex* App::findClosestTrashContainer(User user, TrashType type) {
    auto userLocation=graph->findClosestVertex(user.getX(),user.getY());
    Vertex *selectedTrashContainer;
    double min=INF;
    for(auto t:trashContainers){
        if(t.getType()==type && t.getCurrentCapacity()>0){
            auto temp=Routing::pathCost(Routing::aStar(graph,userLocation,t.getVertex()));
            if(temp<min){
                selectedTrashContainer=t.getVertex();
                min=temp;
            }
        }
    }
    cout<<endl<<selectedTrashContainer->getX()<<endl;
    return selectedTrashContainer;
}

Graph* App::getGraph(){
    return graph;
}

vector<House *> App::getHousesToVisit() {
    vector<House*> housesToVisit;
    for(House * h:houses){
        if(h->getNeedPickUp())
            housesToVisit.push_back(h);
    }
    return housesToVisit;
}

void App::setAdress(User* user){
    Vertex *v = nullptr;
    House* house = nullptr;
    while(house == nullptr){
        while(v == nullptr){
            cout <<"What is your home location ?"<<endl;
            double x = getX();
            double y = getY();
            v = graph->findVertex(x,y);
            if(v == nullptr) cout << "Sorry that localization doesn't exist in our data base" << endl;
        }

        house = new House(v);
        cout << "Your house is set to this coordinates: " << endl;
        cout << "X : " << house->getHouseVertex()->getX() << endl;
        cout << "Y : " << house->getHouseVertex()->getY() << endl;
    }
    houses.push_back(house);
    user->setHouse(house);
}

double App::getX() {
    double x;
    cout << "Enter x:" << endl;
    cin>>x;
    while(cin.fail()){
        cout<<"Invalid input, please select a number: " << endl;
        cin >>x;
    }
    return x;
}

double App::getY() {
    double y;
    cout << "Enter y:" << endl;
    cin >> y;
    while(cin.fail()){
        cout<<"Invalid input, please select a number: " << endl;
        cin >>y;
    }
    return y;
}
vector<GarbageCollectionFacility*> App::getGarbageCFs() {
    return garbageCFs;
}

