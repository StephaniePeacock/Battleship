/* 
 * File:   User.h
 * Author: Stephanie Peacock
 * Created on March 23, 2024, 8:26 PM
 * Purpose: User Class Specification
 */

#include <iostream>  //Input/Output Library
#include <cstring>
using namespace std;

#ifndef USER_H
#define USER_H

const int MAX = 81;

struct Stats {
    int win;
    int loss;
};

class User {
protected:
    char email[MAX];        //dynamic char array
    char pword[MAX];     //dynamic password
    Stats info;
    //add Game info
public:
    User();                         //default
    User(const char*, const char*);           //register new
    User(const char*, const char*, Stats);    //load from db
    virtual ~User();

    //Mutators
    void setEmail(const char*);
    void setPass (const char*);
    
    //Accessors
    const char* getEmail();
    const char* getPass();
    
    //Other Functions
    void display() const;
    void save();
    // User operator=(User &); //override = so we can move account to admin type object
};

#endif /* USER_H */

