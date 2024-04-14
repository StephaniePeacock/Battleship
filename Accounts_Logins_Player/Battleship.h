/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Battleship.h
 * Author: hanne
 *
 * Created on April 14, 2024, 11:13 AM
 */

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <string>

#include "AccountsDB.h"

using namespace std;

const string DBPATH = "data/users.bin";

class Battleship {
private:
    AccountsDB accounts;
public:
    Battleship();
    //Other Functions
    void main();
    void login();
    void reg();
    bool checkEm(string&);
    bool checkPw(string&);
    bool verify(string, string);
};


#endif /* BATTLESHIP_H */

