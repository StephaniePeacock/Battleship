/* 
 * File:   User.cpp
 * Author: hanne
 * 
 * Created on April 14, 2024, 10:42 AM
 */

#include "User.h"
#include "Game.h"
#include "Generics.h"

User::User() {
    email[0] = '\0';
    pword[0] = '\0';
    isadmin = false;
    info.win = 0;
    info.loss = 0;
    //add Game default
}

User::User(const string em, const string pw, const bool adm) {  //for registering a new user
    safeCStrNCpy(this->email, em, user::MAXSTR);
    safeCStrNCpy(this->pword, pw, user::MAXSTR);
    safeCStrNCpy(this->sgame, "", game::MAXUID);
    this->isadmin = adm;
    this->info = Stats {0, 0};
    //add Game default
}

User::User(const string em, const string pw, const string gm, Stats s, const bool adm) {  //for loading an existing user
    safeCStrNCpy(this->email, em, user::MAXSTR);
    safeCStrNCpy(this->pword, pw, user::MAXSTR);
    safeCStrNCpy(this->sgame, gm, game::MAXUID);
    isadmin = adm;
    info.win = s.win;
    info.loss = s.loss;
    //add Game object
}

// Static members
GamesDB User::gamesdb = GamesDB(user::GAMESDBPATH);


// Accessors & Mutators
void User::setEmail(const string em) {
    safeCStrNCpy(this->email, em, user::MAXSTR);
}

const string User::getEmail() const{
    return this->email;
}

void User::setPword(const string pw) {
    safeCStrNCpy(this->pword, pw, user::MAXSTR);
}

const string User::getPword() {
    return this->pword;
}

void User::setSGame(const string gm) {
    safeCStrNCpy(this->sgame, gm, game::MAXUID);
}

const string User::getSGame() {
    return this->sgame;
}

const bool User::isAdmin() {
    return this->isadmin;
}

void User::setAdmin (const bool adm) {
    this->isadmin = adm;
}

// Other Functions

string User::newGameUID() {
    // Get timestamp in milliseconds since epoch
    uint64_t now = chrono::duration_cast<chrono::milliseconds>(
        chrono::system_clock::now().time_since_epoch()
    ).count();
    return email + (string)"_" + to_string(now);
}

void User::display() const{
    cout << "Email: " << this->email << "\n";
    cout << "Password: " << this->pword << "\n";
    cout << "Wins: " << this->info.win << "\n";
    cout << "Losses: " << this->info.loss << "\n";
    cout << "Saved Game: " << (strlen(this->sgame) > 0 ? "Yes" : "No") << "\n";
//    cout << "Saved Game UID: \"" << this->sgame << "\"\n";  //DEBUG
}

void User::newGame() {
    
    bool cont = true, save = false;
    int choice;

    // Instantiate Player 1 (Human player)
    Player p1 = Player();

    // Instantiate Player 2
    Player p2;
    cout << "Choose player 2\n[1]Human\n[2]AI\n";
    getNumeric<int>(choice);

    while (cont) {
        switch (choice) {
            case 1:  // Human
                p2 = Player();
                cont = false;
                break;
            case 2:  // AI
                p2 = Comp();
                cont = false;
                break;
            default:
                cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";
                break;
        }
    }
    
    // Create new game
    Game game = Game(&p1, &p2, newGameUID());
    
    // Handle running the game
    handleGame(game);
}

void User::loadGame() {
    
    // Check if the user has a game saved
    if (!strlen(this->sgame) > 0) {
        cout << "No saved game available\n";
        return;
    }

    // Load the game or notify if error
    Game game = Game(this->sgame);
    User::gamesdb.open();
    
    int _;  //throwaway
    if (User::gamesdb.find(game.getUID(), _) < 0) {
        cout << "Error: Game not found\n";
        return;
    }
    
    User::gamesdb.load(game);
    User::gamesdb.close();
    
    // Handle running the game
    handleGame(game);
}

void User::handleGame(Game& game) {
    bool save = game.play();
    if (save) {
        User::gamesdb.open();
        User::gamesdb.del(this->sgame);
        User::gamesdb.save(game);
        User::gamesdb.close();
        this->setSGame(game.getUID());
        cout << "Game saved\n";
    }    
    cout << "Disengaging!\n";
}