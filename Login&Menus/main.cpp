/*
 * File:   main.cpp
 * Author: Stephanie Peacock
 * Created on: 4/05/24 at 6:14PM
 * Purpose:  Battleship Menu
 */

 //System Libraries Here
#include <iostream>  //Input/Output Library
#include <iomanip>   //Format Library
#include <cstdlib>  
#include <ctime>
#include <thread>

using namespace std;

//User Libraries
#include "Battleship.h"
//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes
void menu();
void Quit();
void PlayGame();
bool LoggingIn();
bool Registering();
void Loading();

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set Random Number Seed Here
    srand(static_cast<unsigned int>(time(0)));
    //Declare all Variables Here

    //Input or initialize values Here

    //Launching Game
    Loading();
    PlayGame();

    //Process/Calculations Here

    //Output Located Here

    //Exit
    return 0;
}
void PlayGame() {
    //Declare all Variables Here
    int choice;
    char c;
    bool endgame = false;
    //Switch case within do-while loop to start the game 

    do {
        do
        {
            menu();
            cin >> choice;
            switch (choice)
            {
            case 1:
                endgame = LoggingIn(); break;
            case 2:
                Registering(); break;
            case 3:
                endgame = true; break;
            default:
                cout << "Invalid selection" << endl; break;
            }
        } while (choice >= '1' && choice <= '3');

    } while (!endgame);
    //Quitting game
    Quit();
}
bool LoggingIn() {
    //Declare all variables
    char c = ' ';
    cout << "User creates a new account...running appropriate functions" << endl;
    //User login
    
    //Pulls from database and validates credentials
    
    //if true game starts
    
    // *****if false returns to main menu to create new user
    
    //Prompting User to return to main menu or exit game
    cout << "Would you like to quit or return to main menu" << endl;
    cout << endl << "1 = Quit Game" << endl << "2 = Main Menu " << endl << "Choose: ";
    cin >> c;
    if (toupper(c) == '1') { return true; }
    //returning to main menu and clear terminal
    if (toupper(c) == '2') { system("cls"); return false; }
}
bool Registering() {
    cout << "User creates a new account...running appropriate functions" << endl;
    //get user email and password
    
    // verified they meet requirements
    
    // account gets created and store to database
    
    cout << "User profile has been created, returning to main menu" << endl;
    //returning to main menu after 2 second delay and clearing terminal
    chrono::seconds duration(2);
    this_thread::sleep_for(duration);
    system("cls");
    return false;
    //Registration is complete, returning to main menu
}
void Loading() {
    //Constructing battleship game and thread - duration function for 3 seconds, with terminal clear
    cout << "Loading please wait...";
    chrono::seconds duration(3);
    this_thread::sleep_for(duration);
    system("cls");
    cout << "*************************" << endl;
    cout << "*\t\t\t*" << endl;
    cout << "*\tBattleship \t*" << endl;
    cout << "*\t\t\t*" << endl;
    cout << "*************************" << endl;
}
void menu() {
    //Menu options for the User/Admin
    cout << endl << "Main Menu" << endl;
    cout << endl << "1. Login" << endl;
    cout << "2. Register a new account" << endl;
    cout << "3. Quit Game" << endl;
    cout << "Choose: ";
}
void Quit() {
    //making the user wait specific time before quit program for added realism
    cout << endl << "Exiting Battleship. Farewell Sailor!" << endl;
    //thread - duration function for 3 seconds
    chrono::seconds duration(3);
    this_thread::sleep_for(duration);
}