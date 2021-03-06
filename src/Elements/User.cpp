//
// Created by migue on 04/05/2021.
//

#include "User.h"

#include <utility>

using namespace std;
User::User() {
    userID = 0;
    name = "";
    password = "";
    this->house = nullptr;
}

User::User(int uId, string n, string pass) : userID(uId), name(move(n)), password(move(pass)) {
    this->house = nullptr;
}

int User::getUserId() const {
    return userID;
}

const std::string &User::getName() const {
    return name;
}

const std::string &User::getPassword() const {
    return password;
}

void User::setUserId(int userId) {
    userID = userId;
}

void User::setName(const std::string &name) {
    User::name = name;
}

void User::setPassword(const std::string &password) {
    User::password = password;
}

void User::setPosition(double x, double y) {
    this->x=x;
    this->y=y;
}

double User::getX() const {return this->x;}

double User::getY() const {return this->y;}

void User::setY(double y) {
    this->y=y;
}

void User::setX(double x) {
    this->x=x;
}

House *User::getHouse() const {
    return house;
}

void User::setHouse(House *house) {
    User::house = house;
}
