//
// Created by migue on 04/05/2021.
//

#include "User.h"

#include <utility>

User::User(int uId) : userID(uId) {
    name = "abc xyz";
    password = "abcxyz";
}

User::User(int uId, std::string n, std::string pass) : userID(uId), name(std::move(n)), password(std::move(pass)) {}

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
