/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   AccountsDB.h
 * Author: hanne
 *
 * Created on April 14, 2024, 10:40 AM
 */

#ifndef ACCOUNTSDB_H
#define ACCOUNTSDB_H

#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

#include "User.h"

class AccountsDB {
    public:
        // Member variables
        string fname;
        fstream file;
        
        // Member functions

        AccountsDB();
        AccountsDB(string);
        
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
        
        /// @brief Get the number of records in the database.
        /// @return The number of records in the database.
        int count();

        /// @brief Get the size (in bytes) of the database.
        /// @return The size (in bytes) of the database.
        long int size();

        /// @brief Find a user record in the database.
        /// @param email The email of the user record to find.
        /// @return The index position of the record in the database.
        int find(string email);

        /// @brief Add a new user record to the database.
        /// @param user The user record to add.        
        void add(const User*);

        /// @brief Get a user recrod from the database.
        /// @param pos The index position of the user record to get.
        /// @return The record of the found user. WARNING: Returns dynamically allocated memory.
        void get(int, User*);

        /// @brief Get all user records from the database.
        /// @return A pointer to an array of user records. WARNING: Returns dynamically allocated memory.
        void getAll(User*);

        /// @brief Set the given record at the given index in the database.
        /// @param  pos The index position of the record to set.
        /// @param  user The user record to set.void set(int, const User*);
        void set(int, const User&);

        /// @brief Set all records in the database at once.
        /// @param  users The array of users to write to the database.
        /// @param  cnt The number of records in the array that will be written to the database.
        void setAll(User*, int);

        /// @brief Delete the record at the given index in the database.
        /// @param pos The index position of the user record to delete.
        void del(int);

        /// @brief Delete all records in the database.
        void delAll();
        
        /// @brief Display all users
        void display();
};

#endif /* ACCOUNTSDB_H */

