/* 
 * File:   Battleship.h
 * Authors: Anthony Bliss, Steven Contreres, Leoncio Hermosillo, 
 *          Isaiah Lopez, Stephanie Peacock, Marco Reyes,  
 *          Matthew Rodriguez, Michael Hawara, Allen Yang, 
 *          Hannes Ziegler 
 *
 * Created on April 14, 2024, 11:13 AM
 */

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <string>
#include <fstream>
#include <iostream>
//#include <cstdio>
#include <unordered_map>
#include <sstream>
#include <regex>
#include <chrono>
//#include <thread>

#include "Generics.h"

using namespace std;

const int MINEMAIL = 6;
const int MINPWORD = 7;
const string DBPATH = "data/users.bin";
//Board Constants
const int BOARD_SIZE = 10;
const char EMPTY_CELL = '-';
const char SHIP_CELL = 'S';
const char HIT_CELL = 'X';
const char MISS_CELL = 'O';
//Game Constants
const int MAXUID = 102;  // MAXSTR + 1 (for "_") + 20 (largest 64-bit int is 20 chars wide)
//User Constants
const int MAXSTR = 81;

//Player
enum class PlayerType : short unsigned int  // A flag to aid in reconstructing Player objects from binary
{
    PLAYER,
    COMP
};

class Player {
    private:
        char board[BOARD_SIZE][BOARD_SIZE];
        char shots[BOARD_SIZE][BOARD_SIZE];
        unordered_map<char, int> shipCounts;
        int unsunk;
        // mutators
        //    void setUnsunk();
        void setBoard(int, int, const char);
        void setShots(int, int, const char);
        // other functions
        bool isValidCoordinate(int row, int col)
        {
            return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
        }
        bool isValidPlacement(int, int, int, char);

        bool isCellAlreadyHit(int row, int col)
        {
            return (board[row][col] == HIT_CELL || board[row][col] == MISS_CELL);
        }

    public:
        const static PlayerType TYPE = PlayerType::PLAYER;
        Player();            // constructor
        ~Player();           // destructor
        void displayBoard(); // print current board
        void displayShots();
        void promptShipPlacement();
        void attackCell(int, int, Player *);

        bool placeShip(int, int, int, char, char);

        int getUnsunk() { return this->unsunk; }
        char getBoard(int, int);
        char getShots(int, int);
        static int convToInt(string);
        virtual void serialize(stringstream &, int &);
        virtual void deserialize(stringstream &);
};

//Comp
class Comp : public Player {
    private:
        bool smart;
    public:
        const static PlayerType TYPE = PlayerType::COMP;
        Comp();
        Comp(bool smart);
        void serialize(stringstream&, int&) override;
        void deserialize(stringstream&) override;
};
//Game
class Game {
    private:
        char uid[MAXUID];
        Player *p1; // Polymorphic: Can be Player or Comp
        Player *p2; // Polymorphic: Can be Player or Comp
        bool turn;
        bool clr;  // Flag set when memory dynamically allocated

        // Methods
        void doTurn();

    public:
        Game(Player *p1, Player *p2, string uid);
        void play();
        ~Game();
        void serialize(stringstream&);
        void deserialize(stringstream&);
        Player* getPlayer1();  //DEBUG
        Player* getPlayer2();  //DEBUG
};

//GamesDB
class GamesDB {
    private:
        // Member variables
        string fname;
        fstream file;    
    public:
        GamesDB();
        void open();
        void close();
        static void createDB();
        static void deleteDB();
        int count();
        long int size();
        int find(const string& uid);
        void load(Game& game);
        void save(Game& game);
        void del(const string& uid);
};

//User
struct Stats {
    int win;
    int loss;
};

class User {
protected:
    char email[MAXSTR];
    char pword[MAXSTR];
    bool isadmin;
    Stats info;
    
    //Other functions
    
public:
    User();                                                 //default
    User(const string, const string, const bool);           //register new
    User(const string, const string, Stats, const bool);    //load from db

    //Mutators
    void setEmail(const string);
    void setPword (const string);
    void setAdmin (const bool);
    
    //Accessors
    const string getEmail();
    const string getPword();
    const bool isAsmin();
    
    //Other Functions
    void display() const;
    string newGameUID();
    void saveGame(Game&);
    void loadGame(Game&);
    void newGame(Game&);
    
    // User operator=(User &); //override = so we can move account to admin type object
};

//AccountsDB
class AccountsDB {
    public:
        // Member variables
        string fname;
        fstream file;
        
        // Member functions
        AccountsDB();
        AccountsDB(string);

        void open(); /// @brief Open file stream.       
        void close(); /// @brief Close file stream.
        
        static void createDB(string); /// @brief Create a new database.
                                      /// @param fname The path to the new database.
        
        static void deleteDB(string); /// @brief Delete an existing database.
                                      /// @param fname The path to the database that will be deleted.  
        
        int count(); /// @brief Get the number of records in the database.
                     /// @return The number of records in the database.
        
        long int size(); /// @brief Get the size (in bytes) of the database.
                         /// @return The size (in bytes) of the database.
        
        int find(string email); /// @brief Find a user record in the database.
                                /// @param email The email of the user record to find.
                                /// @return The index position of the record in the database.
                
        void add(const User*); /// @brief Add a new user record to the database.
                               /// @param user The user record to add.
        
        void get(int, User*); /// @brief Get a user recrod from the database.
                              /// @param pos The index position of the user record to get.
                              /// @return The record of the found user. WARNING: Returns dynamically allocated memory.
        
        void getAll(User*); /// @brief Get all user records from the database.
                            /// @return A pointer to an array of user records. WARNING: Returns dynamically allocated memory.
        
        void set(int, const User&); /// @brief Set the given record at the given index in the database.
                                    /// @param  pos The index position of the record to set.
                                    /// @param  user The user record to set.void set(int, const User*);
        
        void setAll(User*, int); /// @brief Set all records in the database at once.
                                 /// @param  users The array of users to write to the database.
                                 /// @param  cnt The number of records in the array that will be written to the database.
        
        void del(int); /// @brief Delete the record at the given index in the database.
                        /// @param pos The index position of the user record to delete.
        
        void delAll(); /// @brief Delete all records in the database.
        
        void display(); /// @brief Display all users
};

//Battleship
class Battleship {
private:
    AccountsDB accounts;
public:
    Battleship();
    //Other Functions
    void main();
    void loading();
    void login();
    void reg();
    bool checkEm(string&);
    bool checkPw(string&);
    bool verify(string, string);
    bool rules();
    void Quit();
    void userMenu(User&);
    bool acctMenu(User&);
    void gameMenu(User);
};



#endif /* BATTLESHIP_H */