//
// Created by sofia on 24/05/21.
//

#ifndef WASTE_APP_MENUPROGRAMMER_H
#define WASTE_APP_MENUPROGRAMMER_H


#include "../Elements/App.h"
#include "UI.h"

class MenuProgrammer {
private:
    static void programmerOptions();
    static void preprocessingOptions();
    static void routingOptions();
    static void testOptions();
    static void preprocessingMenu();
    static void routingMenu(App *app);
    static void testMenu();
public:
    static void programmerMenu(App *app, UI *ui);
};


#endif //WASTE_APP_MENUPROGRAMMER_H
