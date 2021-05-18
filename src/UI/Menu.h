//
// Created by migue on 04/05/2021.
//

#ifndef WASTE_APP_MENU_H
#define WASTE_APP_MENU_H

#include <iostream>
#include <string>
#include "../Elements/User.h"
#include "../Elements/Driver.h"

namespace Menu {
    void frontpage();
    void beginningOptions();
    void mainMenu();
    void userMenu();
    void driverMenu();
    void loginOptions();
    void userOptions(User &user);
    void driverOptions(User &user);


};


#endif //WASTE_APP_MENU_H
