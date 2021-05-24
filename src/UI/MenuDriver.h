//
// Created by sofia on 24/05/21.
//

#ifndef WASTE_APP_MENUDRIVER_H
#define WASTE_APP_MENUDRIVER_H


#include "../Elements/Driver.h"
#include "../Elements/App.h"
#include "UI.h"
#include <iostream>
#include <string>


class MenuDriver {
private:
    static void driverOptions(Driver *driver);
    static Driver* createDriver(App *app);
    static Driver* loginMenu(App *app);
    static void actionsMenu(Driver *driver, App *app,UI *ui);
    static Driver* loginDriver(App *app);
    static void loginOptions();
    static void getLocation(Driver *driver);
public:
    static void driverMenu(App *app,UI *ui);
};


#endif //WASTE_APP_MENUDRIVER_H
