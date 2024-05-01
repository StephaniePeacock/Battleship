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
    this->isadmin = adm;
    this->info = Stats {0, 0};
    //add Game default
}

User::User(const string em, const string pw, Stats s, const bool adm) {  //for loading an existing user
    safeCStrNCpy(email, em, user::MAXSTR);
    safeCStrNCpy(pword, pw, user::MAXSTR);
    isadmin = adm;
    info.win = s.win;
    info.loss = s.loss;
    //add Game object
}

// Static memebers
GamesDB User::gamesdb = GamesDB(user::GAMESDBPATH);


// Accessors & Mutators
void User::setEmail(const string em) {
    safeCStrNCpy(this->email, em, user::MAXSTR);
}

const string User::getEmail() {
    return this->email;
}

void User::setPword(const string pw) {
    safeCStrNCpy(this->pword, pw, user::MAXSTR);
}

const string User::getPword() {
    return this->pword;
}

const bool User::isAsmin() {
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
}
   //Menu options for the non-administrative player
void User::main(){
    //Declare all Variables Here
    int choice;
    bool quit = false;
    //Switch case within do-while loop for user options
    system("cls");
    do {
            cout << "[1] Account\n[2] View Stats\n[3] Play Game\n[4] Logout\n";
            getNumeric<int>(choice);
            switch (choice)
            {
            case 1:
                display();break;
            case 2: 
                acctMenu();break;
            case 3:
                start();break;
               break;
            case 4:
                quit = true;break;    
            default:
                cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";break;
            } 
    } while (!quit);
    //returning to main menu and clearing the terminal
    cout << "Logging out...bye world" <<endl;
    system("cls");
}
void User::acctMenu(){
    //Declare all Variables Here
    int choice;
    bool quit = false;
    //Switch case within do-while loop for user submenu options
    system("cls");
    do {
            cout << "[1] Change email\n[2] Update Password\n[3] Delete Account\n[4] Go Back\n";
            getNumeric<int>(choice);
            switch (choice)
            {
            case 1:
                cout << "Changing email";break;
            case 2: 
                cout << "Updating password";break;
            case 3:
                cout << "Deleting account";break;
            case 4:
                quit = true;break;    
            default:
                cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";break;
            } 
    } while (!quit);
    //returning to user menu
    system("cls");
}
void User::start(){
    //Declare all Variables Here
    int choice;
    bool quit = false;
    //Switch case within do-while loop for Game menu
    system("cls");
    do {
            cout << "[1] New Campaign\n[2] Load Campaign\n[3] Go Back\n";
            getNumeric<int>(choice);
            switch (choice)
            {
            case 1:
                cout << "Launching a new game";
                newGame();
                break;
            case 2: 
                cout << "Recovering pervious game";break;
            case 3:
                quit = true;break;    
            default:
                cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";break;
            } 
    } while (!quit);
}

void User::newGame() {
    
    // Player 1 is the human player
    Player p1 = Player();
    
    // Select player 2 (Human or AI)
    // TODO: Selection player type prompt
    Player p2 = Player();

    // Create game instance
    Game game = Game(&p1, &p2, User::newGameUID());
    game.play();
}