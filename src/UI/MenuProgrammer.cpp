//
// Created by sofia on 24/05/21.
//
#include <iostream>
#include <string>
#include "MenuProgrammer.h"
#include "../Algorithms/Analysis.h"

#define INVALIDOPTION "That's not a valid option! Try again please:"
using namespace std;

void MenuProgrammer::programmerMenu(App *app) {
    char input;
    cout << "Hello Programmer" << endl;

    while (true){
        programmerOptions();
        cin >> input;

        if(cin.fail()) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input) {
            case '1':
                preprocessingMenu();
                break;
            case '2':
                routingMenu(app);
                break;
            case '3':
                testMenu();
                break;
            case '0':
                cout << "Going to the previous menu..." << endl;
                return;
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

void MenuProgrammer::preprocessingMenu() {
    char input;

    while (true){
        preprocessingOptions();
        cin >> input;

        if(cin.fail()) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input) {
            case '1':
                Analysis::preprocessingAnalysisTarjan();
                break;
            case '2':
                Analysis::preprocessingAnalysisKosaraju();
                break;
            case '0':
                cout << "Going to the previous menu..." << endl;
                return;
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

void MenuProgrammer::routingMenu(App *app) {
    char input;

    while (true){
        routingOptions();
        cin >> input;;

        if(cin.fail()) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input) {
            case '1':
                Analysis::aStarAnalysis(app->getGraph());
                break;
            case '2':
                Analysis::dijkstraAnalysis(app->getGraph());
                break;
            case '3':
                Analysis::aStarVsDijkstra(app->getGraph());
                break;
            case '0':
                cout << "Going to the previous menu..." << endl;
                return;
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

void MenuProgrammer::testMenu(){
    char input;

    while (true){
        testOptions();
        cin >> input;

        if(cin.fail()) {
            cout << INVALIDOPTION << endl;
            continue;
        }

        switch (input) {
            case '1':
                Preprocessing::testTarjan();
                break;
            case '2':
                Preprocessing::testKosaraju();
                break;
            case '0':
                cout << "Going to the previous menu..." << endl;
                return;
            default:
                cout << INVALIDOPTION << endl;
        }
    }
}

void MenuProgrammer::preprocessingOptions(){
    cout<< "===================================="<<endl;
    cout << " 1. Check Tarjan's time efficiency" << endl;
    cout << " 2. Check Kosaraju's time efficiency" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}
void MenuProgrammer::routingOptions(){
    cout<< "===================================="<<endl;
    cout << " 1. Check A*'s time efficiency" << endl;
    cout << " 2. Check Dijkstra's time efficiency" << endl;
    cout << " 3. Compare Dijkstra's algorithm with A*'s algorithm" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}
void MenuProgrammer::testOptions(){
    cout<< "===================================="<<endl;
    cout << " 1. Test Tarjan" << endl;
    cout << " 2. Test Kosaraju" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}

void MenuProgrammer::programmerOptions() {
    cout<< "===================================="<<endl;
    cout << "Here's what you can do: " << endl;
    cout << " 1. Preprocessing Time Efficiency" << endl;
    cout << " 2. Routing Time Efficiency" << endl;
    cout << " 3. Test Algorithms" << endl;
    cout << " 0. Go back" << endl;
    cout<< "===================================="<<endl;
}