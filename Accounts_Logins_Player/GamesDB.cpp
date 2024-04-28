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
//    cout << "OPENING " << fname << "...\n";
    file.open(fname, ios::binary | ios::in | ios::out);
    if (file.fail()) {
        cout << "Error opening file: " << fname << "\n";
    }
}

void GamesDB::close()
{
//    cout << "CLOSING " << fname << "...\n";
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

int GamesDB::size() {
    file.seekg(0L, ios::end);
    return file.tellg();
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
    
    int i = 0;
    file.seekg(cur, ios::beg);
    while (true) {

        // check if there is any data ahead
        if (file.peek() == EOF) {
            break;  // reached the end of the file
        }
        
        // try to read the uid
        file.read(reinterpret_cast<char*>(&seek_uid), sizeof(seek_uid));
        if (file.fail()) {  //game not found;
            cout << "Unexpected error reading game " << seek_uid << "\n";
            break;
        }
        
        if (strcmp(uid.c_str(), seek_uid) == 0) {  //account found
            pos = i;
            break; 
        }
 
        // read game size
        game_size = 0;  // first reset previously read game size
        file.read(reinterpret_cast<char*>(&game_size), sizeof(game_size));

        // skip the game object; go to next
        file.seekg(game_size, ios::cur);  
    
        // update cursor and index position
        cur += sizeof(seek_uid);
        cur += sizeof(game_size);
        cur += game_size;
        
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
    
    string buffer_str = buffer.str();
    if (pos > -1) {  // existing game found; overwrite existing game
        file.seekp(cur, ios::beg);
//        cout << "WRITING EXISTING " << game.getUID() << " TO " << cur << "\n";  //DEBUG
        file.write(buffer_str.c_str(), buffer_str.size());
    } else {  // write new game
        file.seekp(0L, ios::end);
//        cout << "WRITING NEW GAME " << game.getUID() << " TO " << file.tellp() << "\n";  //DEBUG
        file.write(buffer_str.c_str(), buffer_str.size());
    }
    file.flush();
}

void GamesDB::load(Game& game) {
    
    int cur = 0, pos = 0;
    
    // Look for saved game (if exists)
    pos = find(game.getUID(), cur);
    
    if (pos < 0) {  // existing game not found
        cout << "Game " << game.getUID() << " not found\n";  //DEBUG
        return;
    } 

//    cout << "LOADING GAME " << game.getUID() << " AT " << cur << "\n";  //DEBUG
    // Load existing game
    file.seekp(cur, ios::beg);
    game.deserialize(file);
}

void GamesDB::del(const string& uid) {
    int chk_del = 0;  // Seek position of game to delete
    int chk_beg = 0;  // Seek position of chunk to shift left
    int chk_end = size();  // Size of DB
    int chk_sz = 0; // size of chunk to shift left
    int pos = 0;
    
    // Look for saved game (if exists)
    pos = find(uid, chk_del);
    
    if (pos < 0) {  // existing game not found
        cout << "Game " << uid << " not found\n";  //DEBUG
        return;
    }
    
    // Seek to found saved game location
    file.seekg(chk_del, ios::beg);
    
    // read to the end of this saved game (start of next or eof)
    skip();
    chk_beg = file.tellg();  // Get start of chunk to shift left
//    cout  << "CURSOR POS: " << chk_beg << "\n";  //DEBUG

    // get size of chunk to shift left
    chk_sz = chk_end - chk_beg;

    char buffer_a[chk_beg];
    char buffer_b[chk_sz];
    // Read the chunk of bytes up to record to be deleted into buffer
    file.seekg(0L, ios::beg);
    file.read(buffer_a, chk_del);
    // Read the chunk of bytes after record to be deleted into the buffer
    file.seekg(chk_beg, ios::beg);
    file.read(buffer_b, chk_sz);
    
    // Clear file contents;
    delAll();
    
    // Reconstruct file contents (without deleted record)
    file.seekp(0L, ios::end);
    file.write(buffer_a, chk_del);
    file.write(buffer_b, chk_sz);
    
    file.flush();   
}

void GamesDB::skip() {
    int game_size = 0;
    file.seekg(sizeof(char [game::MAXUID]), ios::cur);
    file.read(reinterpret_cast<char*>(&game_size), sizeof(game_size));
    file.seekg(game_size, ios::cur);
}

void GamesDB::list() {
    int pos = -1, cur = 0, game_size = 0;
    char uid[game::MAXUID];
    
    int i = 0;
    file.seekg(cur, ios::beg);
    while (true) {
        
        // Check if there is any data ahead
        if (file.peek() == EOF) {
            break;  // reached the end of the file
        }
        
        // Try to read the uid
        file.read(reinterpret_cast<char*>(&uid), sizeof(uid));
        if (file.fail()) {  //game not found;
            cout << "Unexpected error reading game " << uid << "\n";
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
    file.clear();
}

void GamesDB::delAll(){
    
    // Check if stream is open, close if open, remember initial state
    bool opn = false;
    if (file.is_open()){
        opn = true;
        close();
    }
    
    // Clear all contents from file
    file.open(fname, ios::binary | ios::out | ios::trunc);
    close();

    // If initial state was open, reopen.
    if (opn) {
        open();
    }
}

