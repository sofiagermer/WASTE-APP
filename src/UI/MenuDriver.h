//
// Created by sofia on 24/05/21.
//

#ifndef WASTE_APP_MENUDRIVER_H
#define WASTE_APP_MENUDRIVER_H


#include "../Elements/Driver.h"
#include "../Elements/App.h"

class MenuDriver {
private:
    static void driverOptions(Driver *driver);
    static Driver* createDriver(App *app);
    static Driver* loginMenu(App *app);
    static void actionsMenu(Driver *driver, App *app);
    static Driver* loginDriver(App *app);
    static void loginOptions();
public:
    static void driverMenu(App *app);
};


#endif //WASTE_APP_MENUDRIVER_H
