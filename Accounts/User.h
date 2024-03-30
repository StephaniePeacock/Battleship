/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   User.h
 * Author: hannes
 *
 * Created on March 30, 2024, 7:35 AM
 */

#ifndef USER_H
#define USER_H

const int MAXFLD = 81;

struct Stats {
    int win;
    int loss;
};


// NOTE: This is just a stub for testing.
class User {
    public:
        User(char [MAXFLD], char [MAXFLD]);
        char email[MAXFLD];
        char pword[MAXFLD];
        Stats info;

    private:

};

#endif /* USER_H */

