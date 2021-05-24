//
// Created by sofia on 24/05/21.
//

#include "MenuDriver.h"
#include <iostream>
#include <string>

#define INVALIDOPTION "That's not a valid option! Try again please:"

using namespace std;

void MenuDriver::driverMenu(App *app,UI *ui) {
    Driver *driver = loginMenu(app);
    if(driver == nullptr) return;
    cout << "Hello there " << driver->getName() << endl;
    actionsMenu(driver, app,ui);
}
/* ================================================================================================
 * Drivers Login Menu
 * ================================================================================================
 */
void MenuDriver::loginOptions() {
    cout<< "===================================="<<endl;
    cout << "Tell us what you want to do:" << endl;
    cout << " 1. Log in" << endl;
    cout << " 2. Create an account" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}

Driver* MenuDriver::loginMenu(App *app){
    char input;
    bool endWhile = false;
    Driver *driver = nullptr;
    //ask for credentials
    do {
        cout << "Now we need to know who you are." << endl;
        loginOptions();
        cin >> input;

        if(cin.fail()) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input) {
            case '1':
                cout << "Logging in to an account..." << endl;
                driver = loginDriver(app);
                if(driver == nullptr){
                    cout << "We don't have a driver with that combination!" << endl;
                    break;
                }
                getLocation(driver);
                endWhile = true;
                break;

            case '2':
                cout << "Creating account..." << endl;
                driver = createDriver(app);
                if(driver == nullptr) break;
                getLocation(driver);
                endWhile = true;
                break;

            case '0':
                endWhile = true;
                break;
            default:
                cout << INVALIDOPTION << endl;
                break;
        }
    } while (!endWhile);
    return driver;
}

Driver* MenuDriver::createDriver(App *app) {
    float inputcarmax;
    string username, userpassowrd, carlicenseplate;

    cout << "Hello! Let's create an account for you." << endl;
    cout << "First of all we will need your name:" << endl;
    cin >> username;
    cout << "Next we will need your password:" << endl;
    cin >> userpassowrd;

    cout << "Since you are a driver we need some information about you car" << endl;
    cout << "We need to know your car's license plate" << endl;
    cin >> carlicenseplate;
    cout << "We need to know is how many liters of trash your car can carry" << endl;
    cin >> inputcarmax;

    app->addCar(carlicenseplate, inputcarmax);
    int driverid = app->addDriver(username, userpassowrd, carlicenseplate);
    if(driverid  == -1){
        cout << "ERROR CREATING CAR!" << endl;
        return nullptr;
    }
    Driver* driver = app->findDriver(driverid, userpassowrd);
    if(driver == nullptr){
        cout << "ERROR CREATING DRIVER!" << endl;
        return driver;
    }

    cout << "Your user ID is: " << driver->getUserId() << endl;
    cout << "Your car's license plate is " << driver->getCar()->getLicensePlate() << " And it can hold "
         << driver->getCar()->getMaxCapacity() << " liters of trash" << endl;
    cout << "You are all set, " << driver->getName() << ", don't forget your password and user ID!" << endl;

    return driver;
}


Driver *MenuDriver::loginDriver(App *app) {
    int userid;
    string password;
    cout<< "===================================="<<endl;
    cout << "UserID: " << endl;
    cin >> userid;
    cout << "Password: " << endl;
    cin >> password;
    cout<< "===================================="<<endl;
    return app->findDriver(userid, password);
}

void MenuDriver::getLocation(Driver *driver) {
    double x,y;
    cout<< "===================================="<<endl;
    cout<<"What is your current location ?"<<endl;
    cout << "Enter x:" << endl;
    cin>>x;
    while(cin.fail()){
        cout<<"Invalid input, please select a number: " << endl;
        cin >>x;
    }
    cout << "Enter y:" << endl;
    cin >> y;
    while(cin.fail()){
        cout<<"Invalid input, please select a number: " << endl;
        cin >>y;
    }
    driver->setX(x);
    driver->setY(y);
    cout<< "===================================="<<endl;
}

/* ================================================================================================
 * Drivers Actions Menu
 * ================================================================================================
 */

void MenuDriver::driverOptions(Driver *driver) {
    cout<< "===================================="<<endl;
    cout << "Here's what you can do: " << endl;
    cout << " 1. Get pick up route" << endl;
    cout << " 2. Check amount of money earned" << endl;
    if(driver->getCar() == nullptr) cout << " 1. Input car" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}

void MenuDriver::actionsMenu(Driver *driver, App *app,UI *ui){
    char input;
    while (true){
        driverOptions(driver);
        cin >> input;

        if(cin.fail()) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input) {
            case '1': {
                vector<House *> housesToVisit = app->getHousesToVisit();
                for(auto h:housesToVisit){
                    cout<<h->getHouseVertex()->getX()<<endl;
                }
                queue<Vertex *> route = Routing::nearestNeighbour(app->getGraph(), driver, housesToVisit);
                ui->displayRoute(housesToVisit,route);
                break;
            }
            case '2':
                cout << "You have made " << driver->getMoneyEarned() << "€ with our app!" << endl;
                break;
            case '3':
                if(driver->getCar() == nullptr); //ADICIONAR CARRO;
                else cout << INVALIDOPTION << endl; ////Driver already has a car
                break;
            case '0': {
                cout << "We hope to you see again " << driver->getName() << endl;
                return;
            }
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}