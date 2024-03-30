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
    cout << "User Email: " << user.email << "\n";
    
    cout << "Creating database file if it doesn't exist...\n";
    string db = "test.bin";
    Accnts::create(db);
    
    cout << "Creating instance of database interface...\n";
    Accnts accnts = Accnts(db);
    
    
    
    return 0;
}

