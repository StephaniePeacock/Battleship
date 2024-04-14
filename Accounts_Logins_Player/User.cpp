/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   User.cpp
 * Author: hanne
 * 
 * Created on April 14, 2024, 10:42 AM
 */

#include "User.h"
#include "Generics.h"

User::User() {
    email[0] = '\0';
    pword[0] = '\0';
    info.win = 0;
    info.loss = 0;
    //add Game default
}

User::User(const string em, const string pw) { //for registering a new user
    safeCStrNCpy(this->email, em, MAXSTR);
    safeCStrNCpy(this->pword, pw, MAXSTR);
    this->info = Stats {0, 0};
    //add Game default
}

User::User(const string em, const string pw, Stats s) { //for loading an existing user
    safeCStrNCpy(email, em, MAXSTR);
    safeCStrNCpy(pword, pw, MAXSTR);
    info.win = s.win;
    info.loss = s.loss;
    //add Game object
}

void User::setEmail(const string em) {
    safeCStrNCpy(this->email, em, MAXSTR);
}

const string User::getEmail() {
    return this->email;
}

void User::setPword(const string pw) {
    safeCStrNCpy(this->pword, pw, MAXSTR);
}

const string User::getPword() {
    return this->pword;
}

void User::display() const{
    cout << "Email: " << this->email << "\n";
    cout << "Password: " << this->pword << "\n";
    cout << "Wins: " << this->info.win << "\n";
    cout << "Losses: " << this->info.loss << "\n";
}

