/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   User.h
 * Author: hanne
 *
 * Created on April 14, 2024, 10:42 AM
 */

#ifndef USER_H
#define USER_H

#include <iostream>
#include <cstring>

using namespace std;


const int MAXSTR = 81;

struct Stats {
    int win;
    int loss;
};

class User {
protected:
    char email[MAXSTR];     //dynamic char array
    char pword[MAXSTR];     //dynamic password
    Stats info;
    //add Game info
public:
    User();                                   //default
    User(const string, const string);           //register new
    User(const string, const string, Stats);    //load from db

    //Mutators
    void setEmail(const string);
    void setPword (const string);
    
    //Accessors
    const string getEmail();
    const string getPword();
    
    //Other Functions
    void display() const;
    void save();
    // User operator=(User &); //override = so we can move account to admin type object
};


#endif /* USER_H */

