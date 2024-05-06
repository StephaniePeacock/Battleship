/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   GamesDB.h
 * Author: hanne
 *
 * Created on April 21, 2024, 1:51 PM
 */

#ifndef GAMESDB_H
#define GAMESDB_H

#include <fstream>

using namespace std;

#include "Game.h"

class GamesDB {
private:
    // Member variables
    string fname;
    fstream file;
    
    // Private methods
//    void checkState();  //DEBUG
    
    /// @brief Skip a full saved game record in the database
    void skip();
public:
    GamesDB();
    GamesDB(string);
    
    /// @brief Open file stream.
    void open();

    /// @brief Close file stream.
    void close();

    /// @brief Create a new database.
    /// @param fname The path to the new database.
    static void createDB(string);

    /// @brief Delete an existing database.
    /// @param fname The path to the database that will be deleted.
    static void deleteDB(string);

    int size();

    /// @brief Get the size (in bytes) of the database.
    /// @param uid The unique identifier of the game to find.
    /// @param cur The cursor position found game (search also starts from given value, so only reliable if return value != -1)
    /// @return The size (in bytes) of the database.
    int find(const string& uid, int& cur);

    /// @brief Load a game from the database.
    /// @param game The loaded game (fully restored Game object from saved data).
    void load(Game& game);

    /// @brief Save a game to the database.
    /// @param game The game object to save to the database.
    void save(Game& game);
    
    /// @brief Delete a game from the database.
    /// @param uid The UID of the game to be deleted.
    void del(const string& uid);

    /// @brief List all the games in the database.
    void list();

    /// @brief Delete all the games in the database (empty the database).
    void delAll();
};

#endif /* GAMESDB_H */

