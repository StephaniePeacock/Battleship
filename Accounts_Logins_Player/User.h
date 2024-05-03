/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   User.h
 * Author: hanne
 *
 * Created on April 14, 2024, 10:42 AM
 */

#ifndef USER_H
#define USER_H

#include <iostream>
#include <cstring>
#include <chrono>

using namespace std;

#include "GamesDB.h"

namespace user {
    const int MAXSTR = 81;
    const string GAMESDBPATH = "data/games.bin";
}

struct Stats {
    int win;
    int loss;
};

class User {
protected:
    char email[user::MAXSTR];
    char pword[user::MAXSTR];
    char sgame[game::MAXUID];
    bool isadmin;
    Stats info;
    
    // Methods
    
    /// @brief Handles initiating game loop and post-game loop exit logic (i.e. save game).
    /// @param game The game instance to handle.
    void handleGame(Game& game);
    
    //static members
    
    static GamesDB gamesdb;
    
public:
    User();                                                 //default
    User(const string, const string, const bool);           //register new
    User(const string, const string, const string, Stats, const bool);    //load from db

    //Mutators
    void setEmail(const string);
    void setPword (const string);
    void setAdmin (const bool);
    
    //Accessors
    const string getEmail() const;
    const string getPword();
    const bool isAdmin();
    
    //Other Functions
    void display() const;
    string newGameUID();
    void loadGame(Game&);
    void newGame();
    // User operator=(User &); //override = so we can move account to admin type object
};

#endif /* USER_H */
