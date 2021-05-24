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

Menu::Menu(App app, UI ui) : app(app), ui(ui){
}

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
    cout<< "===================================="<<endl;
    cout << "Please tell us who you are:" << endl;
    cout << " 1. User" << endl;
    cout << " 2. Driver" << endl;
    cout << " 3. Programmer" << endl;
    cout << " 0. Exit" << endl;
    cout<< "===================================="<<endl;
}

void Menu::mainMenu() {
    string input;

    cout << endl << "Welcome to WASTE-App!" << endl;
    while (true){
        beginningOptions();
        getline(cin, input);

        if(input.size() != 1) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                userMenu();
                break;
            case '2':
                driverMenu();
                break;
            case '3':
                programmerMenu();
                break;
            case '0':
                cout << "Thank you for using WASTE-App, we hope to you see again soon!" << endl;
                return;
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

/* ================================================================================================
 * USER MENU
 * ================================================================================================
 */

void Menu::userMenu() {
    char input;
    bool endWhile = false;
    User* user;

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
                user = createUser();
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
        userOptions(*user);
        cin >> input;

        if(cin.fail()) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input) {
            case '1':
                cout << "Set/change address" << endl;
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

void Menu::loginOptions() {
    cout<< "===================================="<<endl;
    cout << "Tell us what you want to do:" << endl;
    cout << " 1. Log in" << endl;
    cout << " 2. Create an account" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}


void Menu::userOptions(User &user) {
    cout<< "===================================="<<endl;
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
    cout<< "===================================="<<endl;
}

User* Menu::createUser() {
    string username, userpassowrd;

    cout << "Hello! Let's create an account for you." << endl;
    //get users name
    cout << "First of all we will need your name:" << endl;
    cin >> username;
    cout << "Next we will need your password:" << endl;
    cin>> userpassowrd;

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

User * Menu::loginUser() {
    int userid;
    string password;
    cout << "UserID: " << endl;
    cin >> userid;
    cout << "Password: " << endl;
    getline(cin, password);
    return app.findUser(userid, password);
}

void Menu::getLocation(User *user) {
    double x,y;
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
    user->setX(x);
    user->setY(y);
}

void Menu::trashMenu(User *user) {
    string input;

    while (true){
        cout << "What type of trash container do you wish to look for? " << endl;
        trashOptions();
        getline(cin, input);

        if(input.size() != 1) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                cout << "Searching for the closest Paper container..." << endl;
                ui.showTrashContainer(user->getX(),user->getY(),app.findClosestTrashContainer(*user,Paper),Paper) ;
                break;

            case '2':
                cout << "Searching for the closest Plastic container..." << endl;
                ui.showTrashContainer(user->getX(),user->getY(),app.findClosestTrashContainer(*user,Plastic),Plastic);
                break;

            case '3':
                cout << "Searching for the closest Glass container..." << endl;
                ui.showTrashContainer(user->getX(),user->getY(),app.findClosestTrashContainer(*user,Glass),Glass);
                break;

            case '4':
                cout << "Searching for the closest Regular container..." << endl;
                ui.showTrashContainer(user->getX(),user->getY(),app.findClosestTrashContainer(*user,Regular),Regular);
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
    cout<< "===================================="<<endl;
    cout << " 1. Paper" << endl;
    cout << " 2. Plastic" << endl;
    cout << " 3. Glass" << endl;
    cout << " 4. Regular" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}

/* ================================================================================================
 * DRIVER MENU
 * ================================================================================================
 */
void Menu::driverMenu() {
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


Driver *Menu::loginDriver() {
    int userid;
    string password;
    cout << "UserID: " << endl;
    cin >> userid;
    cout << "Password: " << endl;
    getline(cin, password);
    return app.findDriver(userid, password);
}
/* ================================================================================================
 * PROGRAMMER MENU
 * ================================================================================================
 */
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
                preprocessingMenu();
                break;
            case '2':
                routingMenu();
                break;
            case '3':
                testMenu();
                break;
            case '0':
                cout << "Going to the previous menu..." << endl;
                return;
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

void Menu::preprocessingMenu() {
    string input;

    while (true){
        preprocessingOptions();
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
            case '0':
                cout << "Going to the previous menu..." << endl;
                return;
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

void Menu::routingMenu() {
    string input;

    while (true){
        routingOptions();
        getline(cin, input);

        if(input.size() != 1) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                Analysis::aStarAnalysis(app.getGraph());
                break;
            case '2':
                Analysis::dijkstraAnalysis(app.getGraph());
                break;
            case '3':
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

void Menu::testMenu(){
    string input;

    while (true){
        testOptions();
        getline(cin, input);

        if(input.size() != 1) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                Preprocessing::testTarjan();
                break;
            case '2':
                Preprocessing::testKosaraju();
                break;
            case '0':
                cout << "Going to the previous menu..." << endl;
                return;
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

void Menu::preprocessingOptions(){
    cout<< "===================================="<<endl;
    cout << " 1. Check Tarjan's time efficiency" << endl;
    cout << " 2. Check Kosaraju's time efficiency" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}
void Menu::routingOptions(){
    cout<< "===================================="<<endl;
    cout << " 1. Check A*'s time efficiency" << endl;
    cout << " 2. Check Dijkstra's time efficiency" << endl;
    cout << " 3. Compare Dijkstra's algorithm with A*'s algorithm" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}
void Menu::testOptions(){
    cout<< "===================================="<<endl;
    cout << " 1. Test Tarjan" << endl;
    cout << " 2. Test Kosaraju" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}

void Menu::programmerOptions() {
    cout<< "===================================="<<endl;
    cout << "Here's what you can do: " << endl;
    cout << " 1. Preprocessing Time Efficiency" << endl;
    cout << " 2. Routing Time Efficiency" << endl;
    cout << " 3. Test Algorithms" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}