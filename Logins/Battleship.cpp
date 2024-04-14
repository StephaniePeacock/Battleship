 /* 
 * File:   Battleship.cpp
 * Author: Stephanie Peacock
 * Created on March 23, 2024, 9:38 PM
 * Purpose: Battleship. Class Implementation
 */
#include <iostream>
#include <regex>
#include "Battleship.h"
#include "User.h"
#include "GameBoard.h"
//using namespace std;

Battleship::Battleship(){
    cout << "Press 1 to login, 2 to register, anything else to exit: ";
    cin >> choice;
    if(choice == '1'){ login();
    } else if(choice == '2'){ reg();
    } else { cout << "Exiting Battleship. Farewell Sailor!"; } 
    cout << "Begin Game." << endl;
    play();
}

void Battleship::login() {
    cout << "Logging in.";
}

void Battleship::reg() {
    string e, p;
    cout << "Registering account." << endl
         << "Enter your email address: ";
    cin.ignore();
    getline(cin,e);
    //first make sure it's the right size
    while(e.length() < 6 || e.length() > 80){
        cout << "Invalid email length, please re-enter: ";
        getline(cin,e);
    }
    //now verify it's formatted correctly
    while(!checkEm(e)){
        cout << "Invalid email, please re-enter: ";
        getline(cin,e);
    }
    //get the password
    cout << "Enter a password: ";
    getline(cin,p);
    //check & keep trying till we get a valid password
    while(!checkPw(p)){
        cout << "Re-enter password: ";
        getline(cin,p);
    }
    const char* em = e.c_str();
    const char* pw = p.c_str();
    User usr(em,pw);
    usr.display();
    
}

bool Battleship::checkEm(string em) {
    /*Regular expression! declare the pattern first
    * checks local for no . at start or end, no double dots
    * then checks for at exactly 1 @ 
    * lastly checks domain for no . at start or end
    * and at least 2 letters after the last . for top level domain
    */
    const regex pattern(R"(\b[A-Za-z0-9_][A-Za-z0-9._-]*[A-Za-z0-9]@[A-Za-z0-9-]+(?:\.[A-Za-z0-9-]+)*(?:\.[A-Z|a-z]{2,}\b))");
    //now check if the email matches the pattern and return it
    return regex_match(em, pattern);
}

bool Battleship::checkPw(string pw) {
    //initialize all to false
    bool valid = false;
    bool upper = false;
    bool lower = false; 
    bool num   = false;
    //verify it is minimum length
    if(pw.length() > 7 && pw.length() < 81){
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
    //if password isn't long enough bypass the other checks
    } else { cout << "Password must be between 8 and 80 characters long. "; }
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

void Battleship::play(){
    // Create two game boards, one for each player
    GameBoard p1;
    GameBoard p2;
    char row;
    char col;

    // Display player 1's board after ship placement
    cout << "Player 1's Board before ship placement:" << endl;
    p1.displayBoard();
    
    // Prompt player 1 to place ships on the board
    cout << "Player 1, please place your ships:" << endl;
    p1.promptShipPlacement();

    // Display player 1's board after ship placement
    cout << "Player 1's Board after ship placement:" << endl;
    p1.displayBoard();
    
    // Prompt player 2 to place ships on the board
    cout << "Player 2, please place your ships:" << endl;
    p2.promptShipPlacement();

    // Display player 2's board after ship placement
    cout << "Player 1's Board after ship placement:" << endl;
    p2.displayBoard();

    while(p2.getUnsunk() > 0 || p1.getUnsunk() > 0){
        
        cout << "Commence attack. Enter row and col coordinates:" << endl;
        cin >> col >> row;
        p1.attackCell(row, col, p2);
        p1.displayShots();
    }
    
    
}