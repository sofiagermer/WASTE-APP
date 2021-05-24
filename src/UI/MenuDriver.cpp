//
// Created by sofia on 24/05/21.
//

#include "MenuDriver.h"
#include <iostream>
#include <string>
#include "MenuDriver.h"
#include "../Elements/Driver.h"

#define INVALIDOPTION "That's not a valid option! Try again please:"

using namespace std;
void MenuDriver::driverMenu(App *app) {
    string input;
    bool endWhile = false;
    Driver* driver;

    //ask for credentials
    do {
        cout << "Now we need to know who you are." << endl;
        loginOptions();
        getline(cin, input);

        if(input.size() != 1) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                //Log in
                cout << "Logging in to an account..." << endl;
                driver = loginDriver(app);
                if(driver == nullptr){
                    cout << "We don't have a driver with that combination!" << endl;
                    break;
                }
                endWhile = true;
                break;

            case '2':
                //Create account
                cout << "Creating account..." << endl;
                driver = createDriver(app);
                if(driver == nullptr) break;
                endWhile = true;
                break;

            case '0':
                return;

            default:
                cout << INVALIDOPTION << endl;
                break;
        }
    } while (!endWhile);

    //show options
    cout << "Hello there " << driver->getName() << endl;
    while (true){
        driverOptions(*driver);
        getline(cin, input);

        if(input.size() != 1) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                //Set/change car
                cout << "Set/change car" << endl;
                break;
            case '2': {
                vector<House *> housesToVisit = app->getHousesToVisit();
                queue<Vertex *> route = Routing::nearestNeighbour(app->getGraph(), driver, housesToVisit);
                break;
            }
            case '3':
                //Check money
                cout << "You have made " << driver->getMoneyEarned() << "€ with our app!" << endl;
                break;
            case '0': {
                cout << "We hope to you see again " << driver->getName() << endl;
                delete driver;
                return;
            }
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}


void MenuDriver::driverOptions(Driver &driver) {

    //need to change this!
    bool hasPickupRoute = false;

    cout << "Here's what you can do: " << endl;

    if(driver.getCar() != nullptr) cout << " 1. Change car" << endl;
    else cout << " 1. Input car" << endl;

    cout << " 2. Get pick up route" << endl;

    cout << " 3. Check amount of money earned" << endl;

    cout << " 0. Go back" << endl;

}

Driver* MenuDriver::createDriver(App *app) {
    float inputcarmax;
    string username, userpassowrd, carlicenseplate;

    cout << "Hello! Let's create an account for you." << endl;
    //get users name
    cout << "First of all we will need your name:" << endl;
    getline(cin, username);
    //get users password
    cout << "Next we will need your password:" << endl;
    getline(cin, userpassowrd);

    //get drivers car
    cout << "Since you are a driver we need some information about you car" << endl;
    cout << "We need to know your car's license plate" << endl;
    getline(cin, carlicenseplate);
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
    cout << "UserID: " << endl;
    cin >> userid;
    cout << "Password: " << endl;
    getline(cin, password);
    return app->findDriver(userid, password);
}

void MenuDriver::loginOptions() {
    cout<< "===================================="<<endl;
    cout << "Tell us what you want to do:" << endl;
    cout << " 1. Log in" << endl;
    cout << " 2. Create an account" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}