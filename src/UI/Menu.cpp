//
// Created by migue on 04/05/2021.
//

#include "Menu.h"
#include "UI.h"
#include "../Algorithms/Analysis.h"
#include "MenuProgrammer.h"
#include "MenuDriver.h"
#include "MenuUser.h"

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
                MenuUser::userMenu(&app, &ui);
                break;
            case '2':
                MenuDriver::driverMenu(&app);
                break;
            case '3':
                MenuProgrammer::programmerMenu(&app);
                break;
            case '0':
                cout << "Thank you for using WASTE-App, we hope to you see again soon!" << endl;
                return;
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

