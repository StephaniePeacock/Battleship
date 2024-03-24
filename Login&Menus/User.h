/* 
 * File:   User.h
 * Author: Stephanie Peacock
 * Created on March 23, 2024, 8:26 PM
 * Purpose: User Class Specification
 */

#include <string>
using namespace std;

#ifndef USER_H
#define USER_H

struct Stats {
    int win;
    int loss;
};

class User {
protected:
    string email;        //dynamic char array
    string password;     //dynamic password
    Stats info;
    //add Game info
public:
    User();                         //default
    User(string, string);           //register new
    User(string, string, Stats);    //load from db
    virtual ~User();

    //Mutators
    void setEmail(string);
    void setPass (string);
    
    //Accessors
    string getEmail();
    string getPass();
    
    //Other Functions
    // User operator=(User &); //override = so we can move account to admin type object
};

#endif /* USER_H */

