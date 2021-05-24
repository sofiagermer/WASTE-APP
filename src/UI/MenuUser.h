//
// Created by sofia on 24/05/21.
//

#ifndef WASTE_APP_MENUUSER_H
#define WASTE_APP_MENUUSER_H


#include "../Elements/User.h"
#include "../Elements/App.h"
#include "UI.h"

class MenuUser {
private:
    static User* loginMenu(App *app);
    static void actionMenu(User *user, App* app, UI *ui);
    static void userOptions();
    static void actionMenuWH(User *user, App* app, UI *ui);
    static void userOptionsWH();
    static void loginOptions();
    static User* createUser(App *app);
    static User* loginUser(App *app);
    static void getLocation(User *user);
    static void trashMenu(User *user, App * app, UI *ui);
    static void trashOptions();
public:
    static void userMenu(App *app, UI *ui);
};


#endif //WASTE_APP_MENUUSER_H
