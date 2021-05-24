//
// Created by sofia on 24/05/21.
//

#include "MenuUser.h"
#include <iostream>
#include <string>
#include "../Algorithms/Analysis.h"

#define INVALIDOPTION "That's not a valid option! Try again please:"
using namespace std;
void MenuUser::userMenu(App *app, UI *ui) {
    char input;
    bool endWhile = false;
    User* user;

    //ask for credentials
    do {
        cout << "Now we need to know who you are." << endl;
        loginOptions();
        cin >> input;

        if(cin.fail()) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input) {
            case '1':
                //Log in
                cout << "Logging in to an account..." << endl;
                user = loginUser(app);
                if(user == nullptr){
                    cout << "We don't have a user with that combination!" << endl;
                    break;
                }
                endWhile = true;
                break;

            case '2':
                //Create account
                cout << "Creating account..." << endl;
                user = createUser(app);
                if(user == nullptr) break;
                endWhile = true;
                break;

            case '0':
                return;

            default:
                cout << INVALIDOPTION << endl;
                break;
        }
    } while (!endWhile);

    cout << "Hello there " << user->getName() << endl;
    getLocation(user);
    while (true){
        userOptions(*user);
        cin >> input;

        if(cin.fail()) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input) {
            case '1':
                cout << "Set/change address" << endl;
                break;
            case '2': {
                //Set/cancel pickup
                //cout << "Set/cancel pickup" << endl;
                if(user->getHouse() == nullptr){
                    cout << INVALIDOPTION << endl;
                    break;
                }
                if(user->getHouse()->getNeedPickUp()){
                    user->getHouse()->setNeedPickUp(false);
                    cout << "Pick up cancelled" << endl;
                }
                else{
                    double inputAmountoftrash;
                    cout << "Ammout of trash: ";
                    cin >> inputAmountoftrash;
                    user->getHouse()->setNeedPickUp(true);
                    user->getHouse()->setAmountOfTrash(inputAmountoftrash);
                    cout << "Pick up set for " << inputAmountoftrash << "L of trash." << endl;
                }
                break;
            }
            case '3':
                //Search for a specific trash container
                trashMenu(user, app, ui);
                break;
            case '0': {
                cout << "We hope to you see again " << user->getName() << endl;
                return;
            }
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

void MenuUser::loginOptions() {
    cout<< "===================================="<<endl;
    cout << "Tell us what you want to do:" << endl;
    cout << " 1. Log in" << endl;
    cout << " 2. Create an account" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}


void MenuUser::userOptions(User &user) {
    cout<< "===================================="<<endl;
    cout << "Here's what you can do: " << endl;

    if(user.getHouse() != nullptr) {
        cout << " 1. Change address" << endl;
        if(user.getHouse()->getNeedPickUp()) cout << " 2. Cancel pick up" << endl;
        else cout << " 2. Set pick up" << endl;
        cout << " 3. Search for closest trash container " << endl;
    }
    else{
        cout << " 1. Add house address" << endl;
        cout << " 3. Search for closest trash container " << endl;
    }
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}

User* MenuUser::createUser(App *app) {
    string username, userpassowrd;

    cout << "Hello! Let's create an account for you." << endl;
    //get users name
    cout << "First of all we will need your name:" << endl;
    cin >> username;
    cout << "Next we will need your password:" << endl;
    cin>> userpassowrd;

    int userid = app->addUser(username, userpassowrd);
    User* user = app->findUser(userid, userpassowrd);
    if(user == nullptr) {
        cout << "ERROR CREATING USER!" << endl;
        return user;
    }

    cout << "Your user ID is: " << user->getUserId() << endl;
    cout << "You are all set, " << user->getName() << ", don't forget your password and user ID!" << endl;

    return user;
}

User * MenuUser::loginUser(App *app) {
    int userid;
    string password;
    cout << "UserID: " << endl;
    cin >> userid;
    cout << "Password: " << endl;
    getline(cin, password);
    return app->findUser(userid, password);
}

void MenuUser::getLocation(User *user) {
    double x,y;
    cout<<"What is your current location ?"<<endl;
    cout << "Enter x:" << endl;
    cin>>x;
    while(cin.fail()){
        cout<<"Invalid input, please select a number: " << endl;
        cin >>x;
    }
    cout << "Enter y:" << endl;
    cin >> y;
    while(cin.fail()){
        cout<<"Invalid input, please select a number: " << endl;
        cin >>y;
    }
    user->setX(x);
    user->setY(y);
}

void MenuUser::trashMenu(User *user, App *app, UI *ui) {
    string input;

    while (true){
        cout << "What type of trash container do you wish to look for? " << endl;
        trashOptions();
        getline(cin, input);

        if(input.size() != 1) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input[0]) {
            case '1':
                cout << "Searching for the closest Paper container..." << endl;
                ui->showTrashContainer(user->getX(),user->getY(),app->findClosestTrashContainer(*user,Paper),Paper) ;
                break;

            case '2':
                cout << "Searching for the closest Plastic container..." << endl;
                ui->showTrashContainer(user->getX(),user->getY(),app->findClosestTrashContainer(*user,Plastic),Plastic);
                break;

            case '3':
                cout << "Searching for the closest Glass container..." << endl;
                ui->showTrashContainer(user->getX(),user->getY(),app->findClosestTrashContainer(*user,Glass),Glass);
                break;

            case '4':
                cout << "Searching for the closest Regular container..." << endl;
                ui->showTrashContainer(user->getX(),user->getY(),app->findClosestTrashContainer(*user,Regular),Regular);
                break;
            case '0':
                return;

            default:
                cout << INVALIDOPTION << endl;
                break;
        }
    }
}

void MenuUser::trashOptions() {
    cout<< "===================================="<<endl;
    cout << " 1. Paper" << endl;
    cout << " 2. Plastic" << endl;
    cout << " 3. Glass" << endl;
    cout << " 4. Regular" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}