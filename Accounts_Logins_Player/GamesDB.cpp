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
    cout << "OPENING " << fname << "...\n";
    file.open(fname, ios::binary | ios::in | ios::out);
    if (file.fail()) {
        cout << "Error opening file: " << fname << "\n";
    }
}

void GamesDB::close()
{
    cout << "CLOSING " << fname << "...\n";
    file.close();
    if (file.fail()) {
        cout << "Error closing file: " << fname << "\n";
    }
}

//DEBUG
//void GamesDB::checkState() {
//    cout << "File Stream Status\n";
//    cout << " eof bit: " << file.eof() << "\n";
//    cout << " fail bit: " << file.fail() << "\n";
//    cout << " bad bit: " << file.bad() << "\n";
//    cout << " good bit: " << file.good() << "\n";
//    
//}

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

int GamesDB::find(const string& uid, int& cur) {
    
    int pos = -1, game_size = 0;
    char seek_uid[game::MAXUID];
    
//    cout << "SEEKING: " << uid << "\n";
    
    int i = 0;
    file.seekg(cur, ios::beg);
    while (true) {
//        cout << "i: " << i << "\n";  //DEBUG
//        cout << "-BEGINNING POS\n";  //DEBUG
//        cout << " CURS SEEK POS: " << cur << "\n";  //DEBUG
//        cout << " TRUE SEEK POS: " << file.tellg() << "\n";  //DEBUG
        // try to read the uid
        
        if (file.peek() == EOF) {
            cout << "Reached the end\n";
            break;
        }
        
        file.read(reinterpret_cast<char*>(&seek_uid), sizeof(seek_uid));
        if (file.fail()) {  //game not found;
            if (!file.eof()) {
                cout << "Error reading UID\n";
            } 
            break;
        }
//        cout << "UID: " << seek_uid << "\n";  //DEBUG
//        cout << "-POS AFTER UID\n";  //DEBUG
//        cout << "CURS SEEK POS: " << cur << "\n";  //DEBUG
//        cout << "TRUE SEEK POS: " << file.tellg() << "\n";  //DEBUG
        
        if (strcmp(uid.c_str(), seek_uid) == 0) {  //account found
            pos = i;
            break; 
        }
 
        game_size = 0;  // reset game size for next read
        file.read(reinterpret_cast<char*>(&game_size), sizeof(game_size));
//        cout << "-POS AFTER GAME SIZE\n";  //DEBUG
//        cout << "CURS SEEK POS: " << cur << "\n";  //DEBUG
//        cout << "TRUE SEEK POS: " << file.tellg() << "\n";  //DEBUG

        file.seekg(game_size, ios::cur);  // skip the game object; go to next
//        cout << "-POS AFTER SKIP GAME\n";  //DEBUG
//        cout << "CURS SEEK POS: " << cur << "\n";  //DEBUG
//        cout << "TRUE SEEK POS: " << file.tellg() << "\n";  //DEBUG
    
        cur += sizeof(seek_uid);
        cur += sizeof(game_size);
        cur += game_size;
        
//        cout << "-POS FINAL\n";  //DEBUG
//        cout << "CURS SEEK POS: " << cur << "\n";  //DEBUG
//        cout << "TRUE SEEK POS: " << file.tellg() << "\n";  //DEBUG
        
        i++;
    }
    file.clear();
    return pos;
}

void GamesDB::save(Game& game) {
    
    int cur = 0, pos = 0;
    
    // Serialize Game
    stringstream buffer;
    buffer.seekp(0L, ios::end);
    game.serialize(buffer);
    
    // Look for saved game (if exists)
    pos = find(game.getUID(), cur);
    
//    cout << "SAVE TO SEEK POS: " << cur << "\n";
    
    string buffer_str = buffer.str();
    if (pos > -1) {  // existing game found; overwrite existing game
        file.seekp(cur, ios::beg);
        cout << "WRITING EXISTING " << game.getUID() << " TO " << cur << "\n";
        file.write(buffer_str.c_str(), buffer_str.size());
    } else {  // write new game
        file.seekp(0L, ios::end);
        cout << "WRITING NEW GAME " << game.getUID() << " TO " << file.tellp() << "\n";
        file.write(buffer_str.c_str(), buffer_str.size());
    }
    file.flush();
}

void GamesDB::load(Game& game) {
    
    int cur = 0, pos = 0;
    
    // Look for saved game (if exists)
    pos = find(game.getUID(), cur);
    
    if (pos < 0) {  // existing game not found
        cout << "Game " << game.getUID() << " not found\n";
        return;
    } 

    cout << "LOADING GAME " << game.getUID() << " AT " << cur << "\n";
    // Get existing game
    file.seekp(cur, ios::beg);
    game.deserialize(file);
}

void GamesDB::list() {
    int pos = -1, cur = 0, game_size = 0;
    char uid[game::MAXUID];
    
    int i = 0;
    file.seekg(cur, ios::beg);
    while (!file.fail()) {
        // try to read the uid
        file.read(reinterpret_cast<char*>(&uid), sizeof(uid));
        if (file.fail()) {  //game not found;
            if (!file.eof()) {
                cout << "Error reading UID\n";
            } 
            file.clear();
            break;
        }
        
        cout << "-" << i << "-\n";
        cout << " UID: " << uid << "\n";
        cout << " Seek location (bytes): " << cur << "\n"; 
        
        game_size = 0;  // reset game size for next read
        file.read(reinterpret_cast<char*>(&game_size), sizeof(game_size));
        cur += sizeof(uid);
        cur += sizeof(game_size);
        cur += game_size;
        file.seekg(cur, ios::beg);  // skip the game object; go to next
        i++;
        
    }
}

