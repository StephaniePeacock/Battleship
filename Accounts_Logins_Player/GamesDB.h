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
    void skip();
public:
    GamesDB();
    GamesDB(string);
    void open();
    void close();
    static void createDB(string);
    static void deleteDB(string);
//    int count();
    int size();
    int find(const string& uid, int& cur);
    void load(Game& game);
    void save(Game& game);
    void del(const string& uid);
    void list();
    void delAll();
};

#endif /* GAMESDB_H */

