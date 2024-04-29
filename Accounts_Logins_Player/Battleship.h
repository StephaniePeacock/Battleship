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

const int MINEMAIL = 6;
const int MINPWORD = 7;
const string USERSDBPATH = "data/users.bin";

class Battleship {
private:
    AccountsDB accounts;
public:
    Battleship();
    //Other Functions
    void main();
    void menu();
    void gameStudio();
    void login();
    void reg();
    bool checkEm(string&);
    bool checkPw(string&);
    bool verify(string, string);
    void Rules();
    void Quit();
};



#endif /* BATTLESHIP_H */