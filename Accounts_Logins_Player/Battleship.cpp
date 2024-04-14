/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Battleship.cpp
 * Author: hanne
 * 
 * Created on April 14, 2024, 11:13 AM
 */

#include "Battleship.h"
#include "User.h"
#include "Player.h"
#include "Generics.h"

#include <iostream>
#include <regex>
//using namespace std;

Battleship::Battleship(){
    AccountsDB::createDB(DBPATH);
    this->accounts = AccountsDB(DBPATH);
}

void Battleship::main() {

    cout << "--BATTLESHIP--\n";
    
    char choice;
    bool quit = false;
    while (!quit) {
        cout << "[1] Login\n[2] Register\n[3] Exit\n";
        cout << ">> ";
        choice = getSingleChar();
        switch (choice) {
            case '1':  // Log in
                login();
                break;
            case '2':  // Register new user
                reg();
                break;
            case '3':  // Quit
                quit = true;
                break;
            case 'd':  //FOR DEBUG ONLY, display all users
                this->accounts.open();
                this->accounts.display();
                this->accounts.close();
                break;
            default:
                cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";
                break;
        }
    }
    cout << "Exiting Battleship. Farewell Sailor!\n";
}

void Battleship::login() {
    
    string e, p;
    int pos;
    User user;
    
    cout << "Ready yer Morse code, fer we’re about to transmit our login signal!\n";
    
    cout << "Enter your email address: ";
    safeGetLine(e, MAXSTR);

    // Find user
    this->accounts.open();
    pos = this->accounts.find(e);
    if (pos < 0) {
        cout << "That user does not exist\n";
        return;
    }
    this->accounts.close();
    
    cout << "Enter your password: ";
    safeGetLine(p, MAXSTR);

    // Verify
    if (!this->verify(e, p)) {
        cout << "Invalid password\n";
        return;
    }
    
    // Get user
    this->accounts.open();
    this->accounts.get(pos, &user);
    this->accounts.close();
    
    // TODO: user.main(); to show user menu  
}

void Battleship::reg() {
    string e, p;
    cout << "Registering account.\n";
    
    // Get validated e-mail
    cout << "Enter your email address: ";
    while(!checkEm(e)){
        cout << "Invalid email, please re-enter: ";
    }

    // Get validated password
    cout << "Enter a password: ";
    while(!checkPw(p)){
        cout << "Re-enter password: ";
    }
    const char* em = e.c_str();
    const char* pw = p.c_str();
    User usr(em, pw);
    
    // Store new account in database
    this->accounts.open();
    this->accounts.add(&usr);
    this->accounts.close();
    
    cout << "Account registered\n";
}

bool Battleship::checkEm(string& em) {
    /*Regular expression! declare the pattern first
    * checks local for no . at start or end, no double dots
    * then checks for at exactly 1 @ 
    * lastly checks domain for no . at start or end
    * and at least 2 letters after the last . for top level domain
    */
    safeGetLine(em, MINEMAIL, MAXSTR);
    const regex pattern(R"(\b[A-Za-z0-9_][A-Za-z0-9._-]*[A-Za-z0-9]@[A-Za-z0-9-]+(?:\.[A-Za-z0-9-]+)*(?:\.[A-Z|a-z]{2,}\b))");
    //now check if the email matches the pattern and return it
    return regex_match(em, pattern);
}

bool Battleship::checkPw(string& pw) {
    
    //initialize all to false
    bool valid = false;
    bool upper = false;
    bool lower = false; 
    bool num   = false;
    //Get password and verify password length
    safeGetLine(pw, MINPWORD, MAXSTR);
    //verify we have upper, lower, and number - check all at once!
    for(char ch : pw){
        if(isupper(ch)){ upper = true; }
        if(islower(ch)){ lower = true; }
        if(isdigit(ch)){ num   = true; }
    }
    //we met all criteria, set to true
    if(upper && lower && num) { valid = true; }
    //missing something
    if(!upper) { cout << "Password must contain an upper case letter. " << endl; }
    if(!lower) { cout << "Password must contain a lower case letter. "; }
    if(!num)   { cout << "Password must contain a number. "; }
    //send it back baby
    return valid;
}

bool Battleship::verify(string em, string pw) {
    //initialize to false
    bool valid = false;
    //open the database file
    
    //check all records for em
    
    //em found - check if password matches
    
    //if not match found it returns false
    
    return valid;
}

// TODO: --> MOVE THIS TO Game.cpp
//void Battleship::play(){
//    // Create two game boards, one for each player
//    Player* p1;
//    Player* p2;
//    char row;
//    char col;
//
//    // Display player 1's board after ship placement
//    cout << "Player 1's Board before ship placement:" << endl;
//    p1.displayBoard();
//    
//    // Prompt player 1 to place ships on the board
//    cout << "Player 1, please place your ships:" << endl;
//    p1.promptShipPlacement();
//
//    // Display player 1's board after ship placement
//    cout << "Player 1's Board after ship placement:" << endl;
//    p1.displayBoard();
//    
//    // Prompt player 2 to place ships on the board
//    cout << "Player 2, please place your ships:" << endl;
//    p2.promptShipPlacement();
//
//    // Display player 2's board after ship placement
//    cout << "Player 1's Board after ship placement:" << endl;
//    p2.displayBoard();
//
//    while(p2.getUnsunk() > 0 || p1.getUnsunk() > 0){
//        
//        cout << "Commence attack. Enter row and col coordinates:" << endl;
//        cin >> col >> row;
//        p1.attackCell(row, col, p2);
//        p1.displayShots();
//    }
//}
    

