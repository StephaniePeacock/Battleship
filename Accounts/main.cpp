/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: hanne
 *
 * Created on March 30, 2024, 7:35 AM
 */

#include <iostream>

using namespace std;

#include "User.h"
#include "Accnts.h"

/*
 * 
 */
int main() {
    
    User user = User("hansintheair@email.com", "pwd");
    
    cout << "Creating database file if it doesn't exist...\n";
    string db = "users.bin";
    Accnts::create(db);
    
    cout << "Creating instance of database interface...\n";
    Accnts accnts = Accnts(db);

    cout << "Opening database for processing...\n";
    accnts.open();
    
    cout << "Adding a user...\n";
    accnts.add(user);
    
    cout << "There are " << accnts.count() << " users in the database.\n";
    
    User tuser;
    cout << "\nShowing first user in database:\n";
    tuser = accnts.get(0);
    tuser.display();    
    cout << "\nShowing last user in database:\n";
    tuser = accnts.get(accnts.count()-1);
    tuser.display();
    
    cout << "Closing database...\n";
    accnts.close();

    
    return 0;
}

