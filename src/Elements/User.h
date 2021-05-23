//
// Created by migue on 04/05/2021.
//

#ifndef WASTE_APP_USER_H
#define WASTE_APP_USER_H

#include <iostream>
#include <string>
#include "House.h"

using namespace std;

class User {
private:
    /**
     * Defines the user and helps to identify him/her
     */
    int userID;

    /**
     * User's name, used for identification purposes
     */
    string name;

    /**
     * User's password
     */
    string password;

    /*
     * User's position
     */
    double x;
    double y;

    House* house;
public:
    User();

    User(int uId);

    User(int uId, string n, string pass);

    void setUserId(int userId);

    void setName(const string &name);

    void setPosition(double x,double y);

    double getX() const;

    void setX(double x);

    void setY(double y);

    double getY() const;

    void setPassword(const string &password);

    int getUserId() const;

    const string &getName() const;

    const string &getPassword() const;

    House *getHouse() const;

    void setHouse(House *house);


    /**
     * Input operator.
     */
    friend std::istream& operator>>(std::istream& input, User &u);
    /**
     * Output operator.
     */
    friend std::ostream& operator<<(std::ostream& output, const User &u);
};


#endif //WASTE_APP_USER_H
