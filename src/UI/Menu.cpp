//
// Created by migue on 04/05/2021.
//

#include "Menu.h"

void Menu::frontpage(){
    std::cout << "=======================================================================================================" << std::endl;
    std::cout << "  __          _____     _____________________________                  ___      ________   ________" << std::endl;
    std::cout << "  \\ \\        / /   \\  /  ___________   ___|  ________|                /   \\    |  _____  \\|  _____  \\" << std::endl;
    std::cout << "   \\ \\  /\\  / / /_\\ \\ | |_______    | |   |  |_______    _____       / /_\\ \\   | |_____|  | |_____|  |" << std::endl;
    std::cout << "    \\ \\/  \\/ / _____ \\\\_______  \\   | |   |  ________|  |_____|     / _____ \\  |  _______/|  _______/" << std::endl;
    std::cout << "     \\  /\\  / /     \\ \\_______| |   | |   |  |_______              / /     \\ \\ | |        | |" << std::endl;
    std::cout << "      \\/  \\/_/       \\_\\________/   |_|   |__________|            /_/       \\_\\|_|        |_|" << std::endl;
    std::cout << std::endl;
    std::cout << "=======================================================================================================" << std::endl;

}

void Menu::beginningOptions(){
    std::cout << "Please tell us who you are:" << std::endl;
    std::cout << " 1. User" << std::endl;
    std::cout << " 2. Driver" << std::endl;
    std::cout << " 9. Exit" << std::endl;
}

void Menu::mainMenu() {
    std::string input;

    //read files with users and drivers accounts infos

    Menu::frontpage();

    std::cout << std::endl << "Welcome to WASTE-App!" << std::endl;
    while (true){
        Menu::beginningOptions();
        std::getline(std::cin, input);

        if(input.size() != 1) {
            std::cout << INVALIDOPTION << std::endl;
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
            case '9':
                std::cout << "Thank you for using WASTE-App, we hope to you see again soon!" << std::endl;
                return;
            default:
                std::cout << INVALIDOPTION << std::endl;
        }
    }
}

void Menu::userMenu() {
    std::string input;
    bool endWhile = false;
    User* user = new User(rand() * 1000);

    //ask for credentials
    do {
        std::cout << "Now we need to know who you are." << std::endl;
        Menu::loginOptions();
        std::getline(std::cin, input);

        if(input.size() != 1) {
            std::cout << INVALIDOPTION << std::endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                //Log in
                std::cout << "Logging in to an account..." << std::endl;
                //DO AFTER IMPLEMENTING A CLASS THAT SAVES USER'S INFOS!!!
                endWhile = true;
                break;

            case '2':
                //Create account
                std::cout << "Creating account..." << std::endl;
                Menu::createUser(user);
                endWhile = true;
                break;

            case '9':
                return;

            default:
                std::cout << INVALIDOPTION << std::endl;
                break;
        }
    } while (!endWhile);

    //Get User

    //show options
    std::cout << "Hello there " << user->getName() << std::endl;
    while (true){
        Menu::userOptions(*user);
        std::getline(std::cin, input);

        if(input.size() != 1) {
            std::cout << INVALIDOPTION << std::endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                //Set/change address
                std::cout << "Set/change address" << std::endl;
                break;
            case '2':
                //Set/cancel pickup
                std::cout << "Set/cancel pickup" << std::endl;
                break;
            case '9': {
                std::cout << "we hope to you see again " << user->getName() << std::endl;
                delete user;
                return;
            }
            default:
                std::cout << INVALIDOPTION << std::endl;
        }
    }
}

void Menu::driverMenu() {
    std::string input;
    bool endWhile = false;
    auto* driver = new Driver(rand() * 1000);

    //ask for credentials
    do {
        std::cout << "Now we need to know who you are." << std::endl;
        Menu::loginOptions();
        std::getline(std::cin, input);

        if(input.size() != 1) {
            std::cout << INVALIDOPTION << std::endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                //Log in
                std::cout << "Logging in to an account..." << std::endl;
                //DO AFTER IMPLEMENTING A CLASS THAT SAVES DRIVER'S INFOS!!!
                endWhile = true;
                break;

            case '2':
                //Create account
                std::cout << "Creating account..." << std::endl;
                Menu::createDriver(driver);
                endWhile = true;
                break;

            case '9':
                return;

            default:
                std::cout << INVALIDOPTION << std::endl;
                break;
        }
    } while (!endWhile);

    //show options
    std::cout << "Hello there " << driver->getName() << std::endl;
    while (true){
        Menu::driverOptions(*driver);
        std::getline(std::cin, input);

        if(input.size() != 1) {
            std::cout << INVALIDOPTION << std::endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                //Set/change car
                std::cout << "Set/change car" << std::endl;
                break;
            case '2':
                //Set/cancel pickup route
                std::cout << "Set/cancel pickup route" << std::endl;
                break;
            case '9': {
                std::cout << "we hope to you see again " << driver->getName() << std::endl;
                delete driver;
                return;
            }
            default:
                std::cout << INVALIDOPTION << std::endl;
        }
    }
}

void Menu::loginOptions() {
    std::cout << "Tell us what you want to do:" << std::endl;
    std::cout << " 1. Log in" << std::endl;
    std::cout << " 2. Create an account" << std::endl;
    std::cout << " 9. Go back" << std::endl;
}

void Menu::userOptions(User &user) {
    //need to change this!!!
    bool hasAddress = false, needsPickup = false;

    std::cout << "Here's what you can do: " << std::endl;

    if(hasAddress)
        std::cout << " 1. Change address" << std::endl;
    else
        std::cout << " 1. Input address" << std::endl;

    if(needsPickup)
        std::cout << " 2. Cancel pick up" << std::endl;
    else
        std::cout << " 2. Set pick up" << std::endl;

    std::cout << " 9. Go back" << std::endl;
}

void Menu::driverOptions(Driver &driver) {

    //need to change this!!!
    bool hasPickupRoute = false;

    std::cout << "Here's what you can do: " << std::endl;

    if(driver.getCar() != nullptr) std::cout << " 1. Change car" << std::endl;
    else std::cout << " 1. Input car" << std::endl;

    if(hasPickupRoute) std::cout << " 2. Cancel pick up route" << std::endl;
    else std::cout << " 2. Set pick up route" << std::endl;

    std::cout << " 9. Go back" << std::endl;

}

void Menu::createUser(User *user) {
    std::string input;

    std::cout << "Hello! Let's create an account for you." << std::endl;
    //get users name
    std::cout << "First of all we will need your name:" << std::endl;
    std::getline(std::cin, input);
    user->setName(input);
    //get users password
    std::cout << "Next we will need your password:" << std::endl;
    std::getline(std::cin, input);
    user->setPassword(input);

    std::cout << "Your user ID is: " << user->getUserId() << std::endl;
    std::cout << "You are all set, " << user->getName() << ", don't forget your password and user ID!" << std::endl;

    //INSERIR USER NO VETOR!!!
}

void Menu::createDriver(Driver *driver) {
    std::string input;
    float inputcarmax;

    driver->setUserId(rand() * 1000);

    std::cout << "Hello! Let's create an account for you." << std::endl;
    //get users name
    std::cout << "First of all we will need your name:" << std::endl;
    std::getline(std::cin, input);
    driver->setName(input);
    //get users password
    std::cout << "Next we will need your password:" << std::endl;
    std::getline(std::cin, input);
    driver->setPassword(input);
    //get drivers car
    std::cout << "Since you are a driver we need some information about you car" << std::endl;
    std::cout << "All we need to know is how many liters of trash your car can carry" << std::endl;
    std::cin >> inputcarmax;
    driver->setCar(new Car(inputcarmax));

    std::cout << "Your user ID is: " << driver->getUserId() << std::endl;
    std::cout << "You are all set, " << driver->getName() << ", don't forget your password and user ID!" << std::endl;

    //INSERIR USER NO VETOR!!!
}