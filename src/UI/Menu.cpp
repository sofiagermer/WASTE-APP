//
// Created by migue on 04/05/2021.
//

#include "Menu.h"
#include "UI.h"
#include "../Algorithms/Analysis.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void Menu::frontpage(){
    cout << "=======================================================================================================" << endl;
    cout << "  __          _____     _____________________________                  ___      ________   ________" << endl;
    cout << "  \\ \\        / /   \\  /  ___________  ___|  ________|                /   \\    |  _____  \\|  _____  \\" << endl;
    cout << "   \\ \\  /\\  / / /_\\ \\ | |_______    | |  |  |_______    _____       / /_\\ \\   | |_____|  | |_____|  |" << endl;
    cout << "    \\ \\/  \\/ / _____ \\\\_______  \\  | |  |  ________|  |_____|     / _____ \\  |  _______/|  _______/" << endl;
    cout << "     \\  /\\  / /     \\ \\_______| |    | |  |  |_______            / /     \\ \\ | |        | |" << endl;
    cout << "      \\/  \\/_/       \\_\\________/    |_|  |__________|          /_/       \\_\\|_|        |_|" << endl;
    cout << endl;
    cout << "=======================================================================================================" << endl;
    sleep(3);
    cout<<endl<<endl;
}

void Menu::beginningOptions(){
    cout << "Please tell us who you are:" << endl;
    cout << " 1. User" << endl;
    cout << " 2. Driver" << endl;
    cout << " 3. Programmer" << endl;
    cout << " 0. Exit" << endl;
}

void Menu::mainMenu() {
    string input;

    cout << endl << "Welcome to WASTE-App!" << endl;
    while (true){
        Menu::beginningOptions();
        getline(cin, input);

        if(input.size() != 1) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                //Users Menu
                Menu::userMenu();
                break;
            case '2':
                //Drivers Menu
                Menu::driverMenu();
                break;
            case '3':
                //Programmers Menu
                Menu::programmerMenu();
                break;
            case '0':
                cout << "Thank you for using WASTE-App, we hope to you see again soon!" << endl;
                return;
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

void Menu::userMenu() {
    string input;
    bool endWhile = false;
    User* user;

    //ask for credentials
    do {
        cout << "Now we need to know who you are." << endl;
        Menu::loginOptions();
        getline(cin, input);

        if(input.size() != 1) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                //Log in
                cout << "Logging in to an account..." << endl;
                user = loginUser();
                if(user == nullptr){
                    cout << "We don't have a user with that combination!" << endl;
                    break;
                }
                endWhile = true;
                break;

            case '2':
                //Create account
                cout << "Creating account..." << endl;
                user = Menu::createUser();
                if(user == nullptr) break;
                endWhile = true;
                break;

            case '0':
                return;

            default:
                cout << INVALIDOPTION << endl;
                break;
        }
    } while (!endWhile);

    cout << "Hello there " << user->getName() << endl;
    getLocation(user);
    while (true){
        Menu::userOptions(*user);
        getline(cin, input);

        if(input.size() != 1) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                //Set/change address
                cout << "Set/change address" << endl;
                //Idk how to this!!!
                break;
            case '2': {
                //Set/cancel pickup
                //cout << "Set/cancel pickup" << endl;
                if(user->getHouse() == nullptr){
                    cout << INVALIDOPTION << endl;
                    break;
                }
                if(user->getHouse()->getNeedPickUp()){
                    user->getHouse()->setNeedPickUp(false);
                    cout << "Pick up cancelled" << endl;
                }
                else{
                    double inputAmountoftrash;
                    cout << "Ammout of trash: ";
                    cin >> inputAmountoftrash;
                    user->getHouse()->setNeedPickUp(true);
                    user->getHouse()->setAmountOfTrash(inputAmountoftrash);
                    cout << "Pick up set for " << inputAmountoftrash << "L of trash." << endl;
                }
                break;
            }
            case '3':
                //Search for a specific trash container
                trashMenu(user);
                break;
            case '0': {
                cout << "We hope to you see again " << user->getName() << endl;
                return;
            }
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

void Menu::driverMenu() {
    string input;
    bool endWhile = false;
    Driver* driver;

    //ask for credentials
    do {
        cout << "Now we need to know who you are." << endl;
        Menu::loginOptions();
        getline(cin, input);

        if(input.size() != 1) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                //Log in
                cout << "Logging in to an account..." << endl;
                driver = Menu::loginDriver();
                if(driver == nullptr){
                    cout << "We don't have a driver with that combination!" << endl;
                    break;
                }
                endWhile = true;
                break;

            case '2':
                //Create account
                cout << "Creating account..." << endl;
                driver = Menu::createDriver();
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
        Menu::driverOptions(*driver);
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
            case '2':
                //Set/cancel pickup route
                cout << "Set/cancel pickup route" << endl;
                break;
            case '3':
                //Check money
                cout << "You have made " << driver->getMoneyEarned() << "€ with our app!" << endl;
                break;
            case '0': {
                cout << "we hope to you see again " << driver->getName() << endl;
                delete driver;
                return;
            }
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

void Menu::loginOptions() {
    cout << "Tell us what you want to do:" << endl;
    cout << " 1. Log in" << endl;
    cout << " 2. Create an account" << endl;
    cout << " 0. Go back" << endl;
}

void Menu::userOptions(User &user) {
    cout << "Here's what you can do: " << endl;

    if(user.getHouse() != nullptr) {
        cout << " 1. Change address" << endl;
        if(user.getHouse()->getNeedPickUp()) cout << " 2. Cancel pick up" << endl;
        else cout << " 2. Set pick up" << endl;
        cout << " 3. Search for closest trash container " << endl;
    }
    else{
        cout << " 1. Add house address" << endl;
        cout << " 3. Search for closest trash container " << endl;
    }
    cout << " 0. Go back" << endl;
}

void Menu::driverOptions(Driver &driver) {

    //need to change this!
    bool hasPickupRoute = false;

    cout << "Here's what you can do: " << endl;

    if(driver.getCar() != nullptr) cout << " 1. Change car" << endl;
    else cout << " 1. Input car" << endl;

    if(hasPickupRoute) cout << " 2. Cancel pick up route" << endl;
    else cout << " 2. Set pick up route" << endl;

    cout << " 3. Check amount of money earned" << endl;

    cout << " 0. Go back" << endl;

}

User* Menu::createUser() {
    string username, userpassowrd;

    cout << "Hello! Let's create an account for you." << endl;
    //get users name
    cout << "First of all we will need your name:" << endl;
    getline(cin, username);
    //get users password
    cout << "Next we will need your password:" << endl;
    getline(cin, userpassowrd);

    int userid = app.addUser(username, userpassowrd);
    User* user = app.findUser(userid, userpassowrd);
    if(user == nullptr) {
        cout << "ERROR CREATING USER!" << endl;
        return user;
    }

    cout << "Your user ID is: " << user->getUserId() << endl;
    cout << "You are all set, " << user->getName() << ", don't forget your password and user ID!" << endl;

    return user;
}

Driver* Menu::createDriver() {
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

    app.addCar(carlicenseplate, inputcarmax);
    int driverid = app.addDriver(username, userpassowrd, carlicenseplate);
    if(driverid  == -1){
        cout << "ERROR CREATING CAR!" << endl;
        return nullptr;
    }
    Driver* driver = app.findDriver(driverid, userpassowrd);
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

User * Menu::loginUser() {
    int userid;
    string password;
    cout << "UserID: " << endl;
    cin >> userid;
    cout << "Password: " << endl;
    getline(cin, password);
    return app.findUser(userid, password);
}

Driver *Menu::loginDriver() {
    int userid;
    string password;
    cout << "UserID: " << endl;
    cin >> userid;
    cout << "Password: " << endl;
    getline(cin, password);
    return app.findDriver(userid, password);
}

void Menu::trashMenu(User *user) {
    string input;

    while (true){
        cout << "What type of trash container do you wish to look for? " << endl;
        Menu::trashOptions();
        getline(cin, input);

        if(input.size() != 1) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                //Paper
                cout << "Searching for the closest Paper container..." << endl;
                ui.showTrashContainer(user->getX(),user->getY(),app.findClosestTrashContainer(*user,Paper)) ;
                break;

            case '2':
                //Plastic
                cout << "Searching for the closest Plastic container..." << endl;
                ui.showTrashContainer(user->getX(),user->getY(),app.findClosestTrashContainer(*user,Plastic));
                break;

            case '3':
                //Glass
                cout << "Searching for the closest Glass container..." << endl;
                ui.showTrashContainer(user->getX(),user->getY(),app.findClosestTrashContainer(*user,Glass));
                break;

            case '4':
                //Regular
                cout << "Searching for the closest Metal container..." << endl;
                ui.showTrashContainer(user->getX(),user->getY(),app.findClosestTrashContainer(*user,Regular));
                break;
            case '0':
                return;

            default:
                cout << INVALIDOPTION << endl;
                break;
        }
    }
}

void Menu::trashOptions() {
    cout << " 1. Paper" << endl;
    cout << " 2. Plastic" << endl;
    cout << " 3. Glass" << endl;
    cout << " 4. Regular" << endl;
    cout << " 0. Go back" << endl;
}

void Menu::programmerMenu() {
    string input;
    cout << "Hello Programmer" << endl;

    while (true){
        Menu::programmerOptions();
        getline(cin, input);

        if(input.size() != 1) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                Analysis::preprocessingAnalysisTarjan();
                break;
            case '2':
                Analysis::preprocessingAnalysisKosaraju();
                break;
            case '3':
                Analysis::aStarAnalysis(app.getGraph());
                break;
            case '4':
                Analysis::dijkstraAnalysis(app.getGraph());
                break;
            case '5':
                Analysis::aStarVsDijkstra(app.getGraph());
                break;
            case '0':
                cout << "Going to the previous menu..." << endl;
                return;
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

void Menu::programmerOptions() {
    cout << "Here's what you can do: " << endl;
    cout << " 1. Check Tarjan's time efficiency (PREPROCESSING)" << endl;
    cout << " 2. Check Kosaraju's time efficiency (PREPROCESSING)" << endl;
    cout << " 3. Check A*'s time efficiency (ROUTING)" << endl;
    cout << " 4. Check Dijkstra's time efficiency (ROUTING)" << endl;
    cout << " 5. Compare Dijkstra's algorithm with A*'s algorithm (ROUTING)" << endl;
    cout << " 0. Go back" << endl;
}

Menu::Menu(App app, UI ui) : app(app), ui(ui){
}

void Menu::getLocation(User *user) {
    double x,y;
    char c;
    string input;
    cout<<"What is your current location ?"<<endl;
    cout << "Enter x:" << endl;
    while(true) {
        cin>>x;
        if(x==NULL){
            cout<<INVALIDOPTION<<endl;
            continue;
        }
        else break;
    }
    cout << "Enter y:" << endl;
    while(true) {
        cin>>y;
        if(y==NULL){
            cout<<INVALIDOPTION<<endl;
            continue;
        }
        else break;
    }
    user->setX(x);
    user->setY(y);
    cout<<endl;
}
