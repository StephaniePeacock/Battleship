/* 
 * File:   main.cpp
 * Author: Steven 
 *
 * Created on April 19, 2024, 6:39 PM
 */

#include "Battleship.h"
#include "User.h"
#include "Player.h"
#include "Generics.h"
#include "Game.h"

#include <iostream>
#include <regex>
#include <chrono>
#include <thread>
//using namespace std;

Battleship::Battleship(){
    AccountsDB::createDB(DBPATH);
    this->accounts = AccountsDB(DBPATH);
}
void Battleship::menu(){
    //Menu options for the User/Admin
    cout << endl << "Main Menu" << endl;
    cout << "[1] Login\n[2] Register\n[3] Rules\n[4] Play\n[5] Exit\n";
    cout << ">> ";
}
void Battleship::loading(){
    //Constructing battleship game and thread - duration function for 3 seconds, with terminal clear
    cout << "Loading please wait...";
    chrono::seconds duration(3);
    //this_thread::sleep_for(duration);
    system("cls");
    cout << "8 8888888o          .8.    88888 88888   88888 88888   8 88        8 888888     d888888o.   8 88      8  8 88 8 88888888o" <<endl;  
    cout << "8 88    `88.       .88.        8 88         8 88       8 88        8 88         .`88:' `88. 8 88      8  8 88 8 888    `88." <<endl; 
    cout << "8 88     `88      :888.        8 88         8 88       8 88        8 88         8.`88.   Y8 8 88      8  8 88 8 888     `88" <<endl; 
    cout << "8 88     ,88     . `888.       8 88         8 88       8 88        8 88         `8.`88.     8 88      8  8 88 8 888     ,88" <<endl; 
    cout << "8 88.   ,88'    .8. `888.      8 88         8 88       8 88        8 888888      `8.`88.    8 88      8  8 88 8 888.   ,88'" <<endl; 
    cout << "8 88888888     .8`8. `888.     8 88         8 88       8 88        8 88           `8.`88.   8 88      8  8 88 8 88888888P'" <<endl;  
    cout << "8 88    `88.  .8' `8. `888.    8 88         8 88       8 88        8 88            `8.`88.  8 888888888  8 88 8 888" <<endl;         
    cout << "8 88      88 .8'   `8. `888.   8 88         8 88       8 88        8 88        8b   `8.`88. 8 88      8  8 88 8 888" <<endl;         
    cout << "8 88    ,88'.888888888. `888.  8 88         8 88       8 88        8 88        `8b.  ;8.`88 8 88      8  8 88 8 888" <<endl;         
    cout << "8 8888888P .8'       `8. `888. 8 88         8 88       8 8888888   8 8888888    `Y88P ,88P' 8 88      8  8 88 8 888" <<endl;   
}
void Battleship::main() {
    //Declare all Variables Here
    int choice;
    char c = ' ';
    bool quit = false;
    //Switch case within do-while loop to start the game
    loading();
    do {
        do
        {
            menu();
            cin >> choice;
            switch (choice)
            {
            case 1:
                login();break;
            case 2:
                reg();break;
            case 3:
               quit = Rules(); break;
            case 'd':  //FOR DEBUG ONLY, display all users
                this->accounts.open();
                this->accounts.display();
                this->accounts.close();
                break;
            case 4:
                //Game lets;
                //lets.play();break;
            case 5:
                quit = true;break;
            default:
                cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";break;
            }
        } while (choice >= '1' && choice <= '5');

    } while (!quit);
    //Quitting game
    Quit();
}

void Battleship::login() {
    //Declare variables
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
    //returning to main menu after 2 second delay and clearing terminal
    chrono::seconds duration(2);
   //this_thread::sleep_for(duration);
    system("cls");
    //return false;
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
bool Battleship::Rules(){
     //Declaring variables
    fstream txt;
    char c = ' ';
    string str;
    //Clearing terminal and opening up text file and displaying rules of game
    system("cls");
    txt.open("Rules.txt", ios::in);
    while (getline(txt, str)) {
        cout << str << endl;
    }
    //closing file
    txt.close();
    //Prompting User to return to main menu or exit game
    cout << endl << endl << "Would you like to quit or return to main menu" << endl;
    cout << endl << "1 = Quit Game" << endl << "2 = Main Menu " << endl << "Choose: ";
    cin >> c;
    if (toupper(c) == '1') { return true; }
    //returning to main menu and clear terminal
    if (toupper(c) == '2') { system("cls"); return false; }
}

// TODO: --> MOVE THIS TO Game.cpp
//void Battleship::play(){
//    // Create two game boards, one for each player
//    Player* p1;
//    Player* p2;
//    int row, col;
//    char letter;
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
//   cout << "Player 2's Board after ship placement:" << endl;
//    p2.displayBoard();
//
//    while(p2.getUnsunk() > 0 || p1.getUnsunk() > 0){
//        
//        cout << "Commence attack. Enter row and col coordinates:" << endl;
//        cin >> letter >> row;
//        col = letter - 65;
//        p1.attackCell(row, col, p2);
//        p1.displayShots();
//    }
//}
void Battleship::Quit() {
    //making the user wait specific time before quit program for added realism
    cout << endl << "Exiting Battleship. Farewell Sailor!" << endl;
    //thread - duration function for 3 seconds
    chrono::seconds duration(3);
    //this_thread::sleep_for(duration);
}