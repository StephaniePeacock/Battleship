/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   GamesDB.cpp
 * Author: hanne
 * 
 * Created on April 21, 2024, 1:51 PM
 */

#include "GamesDB.h"

GamesDB::GamesDB()
{
    this->fname = "";
}
GamesDB::GamesDB(string fname)
{
    this->fname = fname;
}

void GamesDB::open()
{
    file.open(fname, ios::binary | ios::in | ios::out);
    if (file.fail()) {
        cout << "Error opening file: " << fname << "\n";
    }
}

void GamesDB::close()
{
    file.close();
    if (file.fail()) {
        cout << "Error closing file: " << fname << "\n";
    }
}

void GamesDB::createDB(string fname)
{

    // check file existence, createDB if doesn't exist
    fstream file;
    file.open(fname, ios::in | ios::binary);
    if (!file)
    {
        file.close();
        file.open(fname, ios::out | ios::binary);
    }
    else
    {
        cout << "File \"" << fname << "\" already exists.\n";
    }
    file.close();
}

void GamesDB::deleteDB(string fname) {
    if (remove(fname.c_str()) != 0) {
        cout << "   Failed to delete file \"" << fname << "\".\n";
    }
    else {
        cout << "   Successfully deleted file \"" << fname << "\".\n";
    }
}

int GamesDB::find(const string& uid, int& curr) {
    
    int pos = -1, game_size;
    char seek_uid[game::MAXUID];
    
    int i = 0;
    file.seekg(curr, ios::beg);
    while (!file.eof()) {
        file.read(reinterpret_cast<char*>(&seek_uid), sizeof(seek_uid));
        cout << "UID " << i << ": " << seek_uid << "\n";  //DEBUG
        if (strcmp(uid.c_str(), seek_uid) == 0) {  //account found
            pos = i;
            break; 
        }
        curr += sizeof(seek_uid);

        game_size = 0;  // reset game size for next read
        file.read(reinterpret_cast<char*>(&game_size), sizeof(game_size));
        curr += sizeof(game_size);
        file.seekg(game_size, ios::cur);  // skip the game object; go to next
        curr += game_size;
        i++;
    }
    return pos;
}

void GamesDB::save(Game& game) {
    game.getUID();
}