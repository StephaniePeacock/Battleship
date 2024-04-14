/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   GameDB.h
 * Author: hanne
 *
 * Created on April 13, 2024, 5:40 PM
 */

#ifndef GAMEDB_H
#define GAMEDB_H

#include "Game.h"

class GameDB {
private:
    GameDB();  // This class cannot be instantiated
    static int findGame(int id);
    static int getUniqueID();
public:
    static Game loadGame(int id);
    static void saveGame(int id, const Game* game);
    static void addGame(Game* game);
    static void delGame(int id);
};

#endif /* GAMEDB_H */

