/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/*
 * File:   Accnts.cpp
 * Author: hanne
 *
 * Created on March 30, 2024, 7:42 AM
 */

#include "Accnts.h"

Accnts::Accnts(string fname)
{
    this->fname = fname;
}

/// @brief Open file stream.
void Accnts::open()
{
    file.open(fname, std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        cout << "Error opening file: " << fname << std::endl;
    }
}

/// @brief Close file stream.
void Accnts::close()
{
    file.close();
}

/// @brief Create a new database.
/// @param fname The path to the new database.

void Accnts::create(string fname)
{

    // check file existence, create if doesn't exist
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

/// @brief Get the number of records in the database.
/// @return The number of records in the database.
int Accnts::count() {
    
    // Get size of file
    int fbytes = size();
    
    // Get size of record
    int rbytes = sizeof(User);
    
    // Calculate and return number of records in database
    return fbytes / rbytes;
}

/// @brief Get the size (in bytes) of the database.
/// @return The size (in bytes) of the database.
long int Accnts::size() {
    file.seekg(0L, ios::end);
    return file.tellg();
}

/// @brief Add a new user record to the database.
/// @param user The user record to add.
void Accnts::add(const User* user)
{
//    user.display();  //DEBUG
    file.seekp(0L, ios::end);
    file.write(reinterpret_cast<const char*>(user), sizeof(User));
    file.flush();
}

/// @brief Find a user record in the database.
/// @param email The email of the user record to find.
/// @return The index position of the record in the database.
int Accnts::fnd(string email)
{
    int i = 0;
    int pos = -1;
    int end = count();
    User* current = nullptr;
//    cout << "Searching for " << email << "\n";  //DEBUG

    while (i < end) {
//        cout << "Searching user #" << i << "\n";  //DEBUG
        current = get(i);
        if (current->email == email) {  //account found
            pos = i;
            break; 
        }
        i++;
    }
    return pos;
}

/// @brief Get a user recrod from the database.
/// @param pos The index position of the user record to get.
/// @return The record of the found user. WARNING: Returns dynamically allocated memory.
User* Accnts::get(int pos)
{
    User* acct = new User;
    
    long int cur = pos * sizeof(User);
    file.seekg(cur, ios::beg);
    file.read(reinterpret_cast<char*>(acct), sizeof(User));
    return acct;
}

/// @brief Get all user records from the database.
/// @return A pointer to an array of user records.
User* Accnts::geta()
{
    int end = count();
    User* users = new User[count()];
    file.seekg(0L, ios::beg);
    for (int i = 0; i < end; i++){
        file.read(reinterpret_cast<char*>(&users[i]), sizeof(User));
    }
    return users;
}

/// @brief Set the given record at the given index in the database.
/// @param  pos The index position of the record to set.
/// @param  user The user record to set.
void Accnts::set(int pos, const User* user)
{
    long int cur = pos * sizeof(User);
    file.seekp(cur, ios::beg);
    file.write(reinterpret_cast<const char*>(user), sizeof(User));
    file.flush();
}

/// @brief Delete the record at the given index in the database.
/// @param pos The index position of the user record to delete.
void Accnts::del(int pos)
{
    // Start position of chunk
    long int sbytes = pos * sizeof(User);  //Start byte of record to del.
    long int ebytes = size();  //Size (bytes) of file
    long int rbytes = sizeof(User);  //Size (bytes) of record
    long int cbytes = ebytes - sbytes - rbytes; //Size (bytes) of chunk to shift
    
    char buffer_a[sbytes];
    char buffer_b[cbytes];
    // Read the chunk of bytes up to record to be deleted into buffer
    file.seekg(0L, ios::beg);
    file.read(buffer_a, sbytes);
    // Read the chunk of bytes after record to be deleted into the buffer
    file.seekg(sbytes + rbytes, ios::beg);
    file.read(buffer_b, cbytes);
    
    // Clear file contents;
    dela();
    
    // Reconstruct file contents (without deleted record)
    file.seekp(0L, ios::end);
    file.write(buffer_a, sbytes);
    file.write(buffer_b, cbytes);
    
    file.flush();    
}
// FAILED ATTEMPT: This leaves the file the same size it was before...
// NOTE: Keeping this around in case I have time to attempt to make this work later...
///// @brief Delete the record at the given index in the database.
///// @param pos The index position of the user record to delete.
//void Accnts::del(int pos)
//{
//    // Start position of chunk
//    long int sbytes = pos * sizeof(User);  //Start byte of record to del.
//    long int ebytes = size();  //Size (bytes) of file
//    long int rbytes = sizeof(User);  //Size (bytes) of record
//    long int cbytes = ebytes - sbytes - rbytes; //Size (bytes) of chunk to shift
//    
//    char buffer[cbytes];
//    // Read the chunk of bytes into the buffer
//    file.seekg(sbytes + rbytes, ios::beg);
//    file.read(buffer, cbytes);
//    // Write the chunk of bytes shifted left by one record
//    file.seekp(sbytes, ios::beg);
//    file.write(buffer, cbytes);
//    
//    
/// @brfile.flush();
//}

/// @brief Delete all records in the database.
void Accnts::dela(){
    
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