//
// Created by migue on 04/05/2021.
//

#ifndef WASTE_APP_USER_H
#define WASTE_APP_USER_H

#include <iostream>
#include <string>

class User {
private:
    /**
     * Defines the user and helps to identify him/her
     */
    int userID;

    /**
     * User's name, used for identification purposes
     */
    std::string name;

    /**
     * User's password
     */
    std::string password;

    /*
     * User's position
     */
    double x;
    double y;

public:
    User();

    User(int uId);

    User(int uId, std::string n, std::string pass);

    void setUserId(int userId);

    void setName(const std::string &name);

    void setPosition(double x,double y);

    double getX() const;;

    double getY() const;;

    void setPassword(const std::string &password);

    int getUserId() const;

    const std::string &getName() const;

    const std::string &getPassword() const;


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
