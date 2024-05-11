/* 
 * File:   Battleship.h
 * Authors: Anthony Bliss, Steven Contreres, Leoncio Hermosillo, 
 *          Isaiah Lopez, Stephanie Peacock, Marco Reyes,  
 *          Matthew Rodriguez, Michael Hawara, Allen Yang, 
 *          Hannes Ziegler 
 *
 * Created on April 14, 2024, 11:13 AM
 * 
 * Purpose: Battleship Class Implementation
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

    // Main menu
    void main();
    void loading();
    void login();
    void reg();
    bool checkEm(string&);
    bool checkPw(string&);
    bool verify(string, string);
    void rules();
    void delUser(const User);
    void updateUser(const User admin);

    // User Menu
    void userMenu(User&);
    
    // Account Menu
    bool acctMenu(User&);
    
    // Game Menu
    void gameMenu(User&);
    
    // Admin Menu
    void adminMenu(const User&);    

};



#endif /* BATTLESHIP_H */