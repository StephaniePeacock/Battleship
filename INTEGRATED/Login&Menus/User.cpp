/* 
 * File:   User.cpp
 * Author: Stephanie Peacock
 * Created on March 23, 2024, 8:26 PM
 * Purpose: User. Class Implementation
 */

#include "User.h"
using namespace std;

User::User() {
    email = "";
    password = "";
    info.win = 0;
    info.loss = 0;
    //add Game default
}

User::User(string em, string pw) { //for registering a new user
    email = em;
    password = pw;
    info.win = 0;
    info.loss = 0;
    //add Game default
}

User::User(string em, string pw, Stats s) { //for loading an existing user
    email = em;
    password = pw;
    info.win = s.win;
    info.loss = s.loss;
    //add Game object
}

User::~User() {
}

