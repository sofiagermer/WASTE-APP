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

void Menu::beginningMenu(){
    std::cout << "Please Tell us who you are:" << std::endl;
    std::cout << " 1. User" << std::endl;
    std::cout << " 2. Driver" << std::endl;
    std::cout << " 3. Exit" << std::endl;
}

void Menu::mainMenu() {
    //read files with users and drivers infos
    std::string input;
    Menu::frontpage();
    std::cout << std::endl << "Welcome to WASTE-APP!" << std::endl;
    while (true){
        Menu::beginningMenu();
        std::getline(std::cin, input);
        switch (input[0]) {
            case '1':
                //Users Menu
                break;
            case '2':
                //Drivers Menu
                break;
            case '3':
                std::cout << "Thank you for using WASTE-APP, we hope to you see again soon!" << std::endl;
                return;
            default:
                std::cout << "That's not a valid option! Try again please:" << std::endl;
        }
    }
}