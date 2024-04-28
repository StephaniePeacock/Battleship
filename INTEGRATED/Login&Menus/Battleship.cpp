/* 
 * File:   Battleship..cpp
 * Author: Stephanie Peacock
 * Created on March 23, 2024, 9:38 PM
 * Purpose: Battleship. Class Implementation
 */
#include <iostream>
#include <cstdlib>  
#include <thread>
#include "Battleship.h"
#include "User.h"
using namespace std;


Battleship::Battleship() {

}

void Battleship::login() {
    cout << "Enter Email address: ";
    cout << "Enter Password: ";
}

void Battleship::reg() {
    string input;
    cout << "Registering account." << endl
        << "Enter your email address: ";
    getline(cin, input);
    //keep trying till we get a valid email
    //get the password
    cout << endl << "Enter a password: ";
    getline(cin, input);
    //check & keep trying till we get a valid password
    while (!checkPw(input)) {
        getline(cin, input);
    }

}

bool Battleship::checkEm(string em) {
    //initialize to false
    bool valid = false;
    //verify there is exactly one @ - can't be first or last

    //copy first half before @ to a new string
    //check first half doesn't start or end with .
    //check first half doesn't have double .
    //check first half is all valid chars (a-z,0-9, -, _ , .)

    //copy second half before @ to a new string
    //check second half doesn't start or end with .
    //check second half doesn't have double .
    //check second half is all valid chars (a-z,0-9, -, .)
    //check that last . is at least 2 chars from end



    return valid;
}

bool Battleship::checkPw(string pw) {
    //initialize all to false
    bool valid = false;
    bool upper = false;
    bool lower = false;
    bool num = false;
    //verify it is minimum length
    if (pw.length() > 7) {
        //verify we have upper, lower, and number - check all at once!
        for (char ch : pw) {
            if (isupper(ch)) { upper = true; }
            if (islower(ch)) { lower = true; }
            if (isdigit(ch)) { num = true; }
        }
        //we met all criteria, set to true
        if (upper && lower && num) { valid = true; }
        //missing something
        if (!upper) { cout << "Password must contain an Upper case. " << endl; }
        if (!lower) { cout << "Password must contain a lower case. "; }
        if (!num) { cout << "Password must contain a number. "; }
        //if password isn't long enough bypass the other checks
    }
    else { cout << "Password must be at least 8 characters long. "; }
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