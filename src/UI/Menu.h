//
// Created by migue on 04/05/2021.
//

#ifndef WASTE_APP_MENU_H
#define WASTE_APP_MENU_H

#include <iostream>
#include <string>
#include "../Elements/User.h"
#include "../Elements/Driver.h"
#include "../Elements/App.h"
#include "UI.h"

#define INVALIDOPTION "That's not a valid option! Try again please:"
/**
 * 1. USER
    1.1 Entrar na conta ( com palavra passe)
        1.1.1. Definir quantidade de lixo que tem para ser levantado
        1.1.2. Procurar lixo mais próximo para um determinado tipo de lixo
            1.1.2.1 Papel
            1.1.2.2.Vidro
               ....
            1.1.2.. Voltar
        1.1.3 Voltar
    1.2 Criar uma conta(dados do user + palavra passe)
        1.2.1. Voltar
2. DRIVER
    2.1 Entrar na conta ( com palavra passe)
        2.1.1 Ver total de dinheiro ganho usando a app
        2.1.2 Pedir uma rota para a sua posição atual
        2.1.3. Voltar
    2.2 Criar uma conta(dados do driver + palavra passe)
    2.3.Voltar
3. PROGRAMADOR
    3.1 Ver o grafo ( graf viewer)
    3.2 (ainda nao temos código mas ver eficiencia dos algoritmos)
 */

using namespace std;

class Menu {
private:
    App app;
    UI ui;
public:

    Menu(App app, UI ui);;
    static void frontpage();
    void beginningOptions();
    void mainMenu();
    void loginOptions();
    void userMenu();
    void driverMenu();
    void userOptions(User &user);
    void driverOptions(Driver &driver);
    User* createUser();
    Driver* createDriver();
    User* loginUser();
    Driver* loginDriver();
    void trashOptions();
    void trashMenu(User *user);
    void programmerMenu();
    void programmerOptions();

    static void getLocation(User *user);

    void preprocessingOptions();
    void routingOptions();
    void testOptions();
    void preprocessingMenu();
    void routingMenu();
    void testMenu();
};


#endif //WASTE_APP_MENU_H
