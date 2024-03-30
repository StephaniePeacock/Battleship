/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   User.cpp
 * Author: hannes
 * 
 * Created on March 30, 2024, 7:35 AM
 */

#include <cstring>
using namespace std;


#include "User.h"

User::User(const char email[MAXFLD], const char pword[MAXFLD]) {
    strncpy(this->email, email, MAXFLD);
    strncpy(this->pword, pword, MAXFLD);
    this->info = Stats {0, 0};
}
User::User() {}

void User::display() const{
    cout << "Email: " << this->email << "\n";
    cout << "Password: " << this->pword << "\n";
    cout << "Wins: " << this->info.win << "\n";
    cout << "Losses: " << this->info.loss << "\n";
}


