/*
 * File:   main.cpp
 * Author: Stephanie Peacock
 * Created on: 3/11/24 at 6:14PM
 * Purpose:  Movie Structures
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
void DemoGame();
void DemoRegister();

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set Random Number Seed Here
    srand(static_cast<unsigned int>(time(0)));
    //Declare all Variables Here
    int choice;

    //Switch case to start the game 
    do
        {
        menu();
            cin >> choice;
            switch (choice)
            {
            case 1:
                DemoGame();break;
            case 2:
                DemoRegister();break;
            case 3:
                Quit();
                break;
            default:
                cout << "Invalid selection" << endl;
                break;
            }
        } while (choice >= '1' && choice <= '3');

    //Input or initialize values Here

    //Process/Calculations Here

    //Output Located Here

    //Exit
    return 0;
}
void DemoGame() {
    cout << "User login and plays game...running appropriate functions" << endl;
    //User logins in
    //Pulls from database and validates credentials
    //if true game starts
    // *****if false returns to main menu to create new user
    
    //Game Ends
    //Returns to main menu

}
void DemoRegister() {
    cout << "User creates a new account...running appropriate functions" << endl;
    //get user email and password
    // verified they meet requirements
    // account gets created and store to database
    //returns to main menu
}
void menu() {
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
    //Menu options for the User/Admin
    cout << "1. Login" << endl;
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