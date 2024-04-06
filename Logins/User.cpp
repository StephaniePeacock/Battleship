/* 
 * File:   User.cpp
 * Author: Stephanie Peacock
 * Created on March 23, 2024, 8:26 PM
 * Purpose: User. Class Implementation
 */


#include "User.h"
using namespace std;

User::User() {
    email[0] = '\0';
    pword[0] = '\0';
    info.win = 0;
    info.loss = 0;
    //add Game default
}

User::User(const char* em, const char* pw) { //for registering a new user
    strncpy(this->email, em, MAX);
    strncpy(this->pword, pw, MAX);
    this->info = Stats {0, 0};
    //add Game default
}

User::User(const char* em, const char* pw, Stats s) { //for loading an existing user
    strncpy(email,em, MAX);
    strncpy(pword,pw, MAX);
    info.win = s.win;
    info.loss = s.loss;
    //add Game object
}

User::~User() {
}

void User::display() const{
    cout << "Email: " << this->email << "\n";
    cout << "Password: " << this->pword << "\n";
    cout << "Wins: " << this->info.win << "\n";
    cout << "Losses: " << this->info.loss << "\n";
}
