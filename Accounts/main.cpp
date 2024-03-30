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
    
    string email = "testing5@email.com";
    string pword = "pwd";
    User user = User(email.c_str(), pword.c_str());
    
    cout << "Creating database file if it doesn't exist...\n";
    string db = "users.bin";
    Accnts::create(db);
    
    cout << "Creating instance of database interface...\n";
    Accnts accnts = Accnts(db);

    cout << "Opening database for processing...\n";
    accnts.open();
    
    cout << "\nDatabase contents:\n\n";
    User* tusers = accnts.geta();  //!This function returns dynamically allocated memory!
    for (int i = 0; i < accnts.count(); i++) {
        tusers[i].display();
    }
    
    cout << "Adding a user...\n";
    accnts.add(&user);
    
    cout << "There are " << accnts.count() << " users in the database.\n";
    
    User* tuser = nullptr; 
    cout << "\nShowing first user in database:\n";
    tuser = accnts.get(0);  //!This function returns dynamically allocated memory!
    tuser->display();    
    cout << "\nShowing last user in database:\n";
    tuser = accnts.get(accnts.count()-1);
    tuser->display();
    
    cout << "\nFinding user that doesn't exist:\n";
    cout << "Position: " << accnts.fnd("DOESNOTEXIST") << "\n";
    
    cout << "\nFinding user that does exist:\n";
    cout << "Position: " << accnts.fnd(email) << "\n";

    cout << "\nChanging the win count of the second-to-last user...\n";
    tuser = accnts.get(accnts.count()-2);
    tuser->info.win += 1;
    accnts.set(accnts.count()-1, tuser);
    cout << "\nShowing second-to-last user in database:\n";
    tuser = accnts.get(accnts.count()-2);
    tuser->display();
    
    cout << "\nClosing database...\n";
    
    // Cleanup
    accnts.close();
    delete tuser;
    tuser = nullptr;
    delete[] tusers;
    tusers = nullptr;

    
    return 0;
}

