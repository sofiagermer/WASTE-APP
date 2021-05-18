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
    //read files with users and drivers accounts infos
    std::string input;
    Menu::frontpage();
    std::cout << std::endl << "Welcome to WASTE-APP!" << std::endl;
    while (true){
        Menu::beginningOptions();
        std::getline(std::cin, input);

        if(input.size() != 1) continue;

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
                std::cout << "Thank you for using WASTE-APP, we hope to you see again soon!" << std::endl;
                return;
            default:
                std::cout << INVALIDOPTION << std::endl;
        }
    }
}

void Menu::userMenu() {
    std::string input;
    bool endWhile = false;
    User* user = new User(0);

    //ask for credentials
    do {
        std::cout << "Now we need to know who you are." << std::endl;
        Menu::loginOptions();
        std::getline(std::cin, input);

        if(input.size() != 1) continue;

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
                delete user;
                user = Menu::createUser();
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
    User* userpt = new User(1);

    //show options
    std::cout << "Hello there " << user->getName() << std::endl;
    while (true){
        Menu::userOptions(*userpt);
        std::getline(std::cin, input);

        if(input.size() != 1) continue;

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
                std::cout << "we hope to you see again" << user->getName() << std::endl;
                delete userpt;
                return;
            }
            default:
                std::cout << INVALIDOPTION << std::endl;
        }
    }

}

void Menu::driverMenu() {
    std::string input;

    //ask for credentials
    std::cout << "Now we need to know who you are." << std::endl;
    Menu::loginOptions();
    //check if valid credentials

    //Get Driver
    //WRONG!!! NEED DRIVER CONSTRUCTOR
    User* userpt = new User(1);

    //show options
    std::string driverName = "cba zyx";
    std::cout << "Hello there " << driverName << std::endl;
    while (true){
        Menu::driverOptions(*userpt);
        std::getline(std::cin, input);

        if(input.size() != 1) continue;

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
                std::cout << "we hope to you see again" << driverName << std::endl;
                delete userpt;
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

void Menu::driverOptions(User &user) {

    //need to change this!!!
    std::string driverName = "cba zyx";
    bool hasCar = false, hasPickupRoute = false;

    std::cout << "Here's what you can do: " << std::endl;

    if(hasCar)
        std::cout << " 1. Change car" << std::endl;
    else
        std::cout << " 1. Input car" << std::endl;

    if(hasPickupRoute)
        std::cout << " 2. Cancel pick up route" << std::endl;
    else
        std::cout << " 2. Set pick up route" << std::endl;

    std::cout << " 9. Go back" << std::endl;

}

User* Menu::createUser() {
    std::string input;
    User user = User(rand() * 1000);

    std::cout << "Hello! Let's create an account for you." << std::endl;
    //get users name
    std::cout << "First of all we will need your name:" << std::endl;
    std::getline(std::cin, input);
    user.setName(input);
    //get users password
    std::cout << "Next we will need your password:" << std::endl;
    std::getline(std::cin, input);
    user.setPassword(input);

    std::cout << "Your user ID is: " << user.getUserId() << std::endl;
    std::cout << "You are all set, " << user.getName() << ", don't forget your password and user ID!" << std::endl;

    //INSERIR USER NO VETOR!!!
    return &user;
}