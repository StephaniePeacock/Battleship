/* 
 * File:   User.cpp
 * Author: hanne
 * 
 * Created on April 14, 2024, 10:42 AM
 */

#include "User.h"
#include "Game.h"
#include "Generics.h"

User::User() {
    email[0] = '\0';
    pword[0] = '\0';
    info.win = 0;
    info.loss = 0;
    //add Game default
}

User::User(const string em, const string pw) { //for registering a new user
    safeCStrNCpy(this->email, em, MAXSTR);
    safeCStrNCpy(this->pword, pw, MAXSTR);
    this->info = Stats {0, 0};
    //add Game default
}

User::User(const string em, const string pw, Stats s) { //for loading an existing user
    safeCStrNCpy(email, em, MAXSTR);
    safeCStrNCpy(pword, pw, MAXSTR);
    info.win = s.win;
    info.loss = s.loss;
    //add Game object
}

void User::setEmail(const string em) {
    safeCStrNCpy(this->email, em, MAXSTR);
}

const string User::getEmail() {
    return this->email;
}

void User::setPword(const string pw) {
    safeCStrNCpy(this->pword, pw, MAXSTR);
}

const string User::getPword() {
    return this->pword;
}

void User::display() const{
    cout << "Email: " << this->email << "\n";
    cout << "Password: " << this->pword << "\n";
    cout << "Wins: " << this->info.win << "\n";
    cout << "Losses: " << this->info.loss << "\n";
}
   //Menu options for the non-administrative player
void User::main(){
    //Declare all Variables Here
    int choice;
    bool quit = false;
    //Switch case within do-while loop for user options
    system("cls");
    do {
            cout << "[1] Account\n[2] View Stats\n[3] Play Game\n[4] Logout\n";
            getNumeric<int>(choice);
            switch (choice)
            {
            case 1:
                display();break;
            case 2: 
                acctMenu();break;
            case 3:
                start();break;
               break;
            case 4:
                quit = true;break;    
            default:
                cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";break;
            } 
    } while (!quit);
    //returning to main menu and clearing the terminal
    cout << "Logging out...bye world" <<endl;
    system("cls");
}
void User::acctMenu(){
    //Declare all Variables Here
    int choice;
    bool quit = false;
    //Switch case within do-while loop for user submenu options
    system("cls");
    do {
            cout << "[1] Change email\n[2] Update Password\n[3] Delete Account\n[4] Go Back\n";
            getNumeric<int>(choice);
            switch (choice)
            {
            case 1:
                cout << "Changing email";break;
            case 2: 
                cout << "Updating password";break;
            case 3:
                cout << "Deleting account";break;
            case 4:
                quit = true;break;    
            default:
                cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";break;
            } 
    } while (!quit);
    //returning to user menu
    system("cls");
}
void User::start(){
    //Declare all Variables Here
    int choice;
    bool quit = false;
    //Switch case within do-while loop for Game menu
    system("cls");
    do {
            cout << "[1] New Campaign\n[2] Load Campaign\n[3] Go Back\n";
            getNumeric<int>(choice);
            switch (choice)
            {
            case 1:
                cout << "Launching a new game";break;
            case 2: 
                cout << "Recovering pervious game";break;
            case 3:
                quit = true;break;    
            default:
                cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";break;
            } 
    } while (!quit);
}