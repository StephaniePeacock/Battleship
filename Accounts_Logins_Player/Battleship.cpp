#include "Battleship.h"
#include "User.h"
#include "Player.h"
#include "Generics.h"
#include "Game.h"

#include <iostream>
#include <regex>
#include <chrono>
#include <thread>
//using namespace std;

Battleship::Battleship(){
    AccountsDB::createDB(USERSDBPATH);
    this->accounts = AccountsDB(USERSDBPATH);
}
void Battleship::loading(){
    //Constructing battleship game and thread - duration function for 3 seconds, with terminal clear
    cout << "Loading please wait...";
//    chrono::seconds duration(3);
    /*
     * if you reached this error then netbeans does not support this_thread function from thread library.
     * function would pause game for as long as we want, perfect for loading games, simulation connecting to and online server etc..
     * can comment out and I will try to find a work around
     */
//    this_thread::sleep_for(duration);
//    system("cls");
    cout << "8 8888888o          .8.    88888 88888   88888 88888   8 88        8 888888     d888888o.   8 88      8  8 88 8 88888888o" <<endl;  
    cout << "8 88    `88.       .88.        8 88         8 88       8 88        8 88         .`88:' `88. 8 88      8  8 88 8 888    `88." <<endl; 
    cout << "8 88     `88      :888.        8 88         8 88       8 88        8 88         8.`88.   Y8 8 88      8  8 88 8 888     `88" <<endl; 
    cout << "8 88     ,88     . `888.       8 88         8 88       8 88        8 88         `8.`88.     8 88      8  8 88 8 888     ,88" <<endl; 
    cout << "8 88.   ,88'    .8. `888.      8 88         8 88       8 88        8 888888      `8.`88.    8 88      8  8 88 8 888.   ,88'" <<endl; 
    cout << "8 88888888     .8`8. `888.     8 88         8 88       8 88        8 88           `8.`88.   8 88      8  8 88 8 88888888P'" <<endl;  
    cout << "8 88    `88.  .8' `8. `888.    8 88         8 88       8 88        8 88            `8.`88.  8 888888888  8 88 8 888" <<endl;         
    cout << "8 88      88 .8'   `8. `888.   8 88         8 88       8 88        8 88        8b   `8.`88. 8 88      8  8 88 8 888" <<endl;         
    cout << "8 88    ,88'.888888888. `888.  8 88         8 88       8 88        8 88        `8b.  ;8.`88 8 88      8  8 88 8 888" <<endl;         
    cout << "8 8888888P .8'       `8. `888. 8 88         8 88       8 8888888   8 8888888    `Y88P ,88P' 8 88      8  8 88 8 888" <<endl;   
}
void Battleship::main() {
    //Declare all Variables Here
    char choice;
    bool quit = false;
    //Switch case within do-while loop to start the game
    loading();
    do {
        cout << endl << "Main Menu" << endl;
        cout << "[1] Login\n[2] Register\n[3] Rules\n[4] Exit\n" << ">> ";
        choice = getSingleChar();  // Get char safely
        switch (choice)
        {
        case '1':
            login();break;
        case '2':
            reg();break;
        case '3':
           quit = Rules(); break;
        case 'a':  //FOR DEBUG ONLY, display all users
            this->accounts.open();
            this->accounts.display();
            this->accounts.close();
            break;
        case 'l':  //FOR DEBUG ONLY, quickly login to test user account and play game
        {   
            User user;
            this->accounts.open();
            this->accounts.get(0, &user);
            this->accounts.close();
            cout << "LOGGING IN AS \n";
            user.display();  //DEBUG
            cout << "\n";
            user.main();
            break;
        }
//        case 'm': { //FOR DEBUG ONLY, make an admin user lol
//            User user = User("admin@org.com", "AdminUser1", true);
//            this->accounts.open();
//            this->accounts.add(&user);
//            this->accounts.close();
//            break;
//        }
        case 'g': {  //FOR DEBUG ONLY, test storing Game object in binary file
            Player p1 = Player();
            Player p2 = Player();
            User user;
            this->accounts.open();
            this->accounts.get(1, &user);
            this->accounts.close();
            string uid = user.newGameUID();
            cout << "GAME UID: " << uid << "\n";
            
            // Do some stuff to modify game state
            p1.placeShip(2, 8, 5, 'V', 'C');
            p1.placeShip(5, 3, 3, 'H', 'S');
            p2.attackCell(3, 3, &p1);
            p2.attackCell(5, 3, &p1);
            cout << "PLAYER 1 BOARD:\n";
            p1.displayBoard();
            cout << "PLAYER 1 SHOTS:\n";
            p1.displayShots();
            cout << "PLAYER 2 BOARD:\n";
            p2.displayBoard();
            cout << "PLAYER 2 SHOTS:\n";
            p2.displayShots();
            
            Game game = Game(&p1, &p2, uid);
            
            stringstream buffer;
            buffer.seekp(0L, ios::end);
            cout << "SEREALIZING GAME...\n";
            game.serialize(buffer);
            cout << "SUCCESSFULLY SERIALIZED GAME!\n";
            buffer.seekg(0L, ios::beg);
            cout << "SET CURSOR TO BEGINNING\n";
            
            char c_uid[102];
            buffer.read(reinterpret_cast<char*>(c_uid), sizeof(c_uid));
            cout << "READ GAME UID: " << c_uid << "\n";
            
            int gsize = 0;
            buffer.read(reinterpret_cast<char*>(&gsize), sizeof(gsize));
            cout << "READ GAME SIZE: " << gsize << "\n";
            
            cout << "DESEREALIZING GAME...\n";
            game.deserialize(buffer);            
            cout << "SUCCESSFULLY DESERIALIZED!\n";
            
            cout << "PLAYER 1\n";
            Player* p1n = game.getP1();
            p1n->displayBoard();
            p1n->displayShots();
            
            cout << "PLAYER 2\n";
            Player* p2n = game.getP2();
            p2n->displayBoard();
            p2n->displayShots();
            
            break;
            }
        case '4':
            quit = true; break;
        default:
            cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";break;
        } 
    } while (!quit);
    //Quitting game
    Quit();
}

void Battleship::login() {
    //Declare variables
    string e, p;
    int pos;
    User user;
    
    cout << "Ready yer Morse code, fer we’re about to transmit our login signal!\n";
    
    cout << "Enter your e-mail address, Captain: ";
    safeGetLine(e, user::MAXSTR);

    // Find user
    this->accounts.open();
    pos = this->accounts.find(e);
    this->accounts.close();
    if (pos < 0) {
        cout << "\nAre ye reporting to the wrong fleet, Captain!?\n";
        cout << "That e-mail is not listed in our logbook.\n";
        return;
    }
    
    cout << "Enter your top secret code: ";
    safeGetLine(p, user::MAXSTR);

    // Verify
    if (!this->verify(e, p)) {
        cout << "Blimey! That's not the right signal. Try again!\n";
        return;
    }
    
    // Get user
    this->accounts.open();
    this->accounts.get(pos, &user);
    this->accounts.close();
    
    //user.display();  //DEBUG
    
    user.main();
    
    //return to main menu
}

void Battleship::reg() {
    string e, p;
    cout << "Ahoy Captain! Ready to enlist?\n";
    
    // Get validated e-mail
    cout << "Enter your email address: ";
    while(!checkEm(e)){
        cout << "Invalid email, please re-enter: ";
    }

    // Get validated password
    cout << "Enter yer top secret code: ";
    while(!checkPw(p)){
        cout << "This ain't no Sunday sail, Captain! Make your code more secure!!: ";
    }
    const char* em = e.c_str();
    const char* pw = p.c_str();
    User usr(em, pw, false);
    
    // Store new account in database
    this->accounts.open();
    this->accounts.add(&usr);
    this->accounts.close();
    
    cout << "Arr! Yer registered with the fleet!\n";
    //returning to main menu after 2 second delay and clearing terminal
//    chrono::seconds duration(2);
   //this_thread::sleep_for(duration);
//    system("cls");
    //return false;
}

bool Battleship::checkEm(string& em) {
    /*Regular expression! declare the pattern first
    * checks local for no . at start or end, no double dots
    * then checks for at exactly 1 @ 
    * lastly checks domain for no . at start or end
    * and at least 2 letters after the last . for top level domain
    */
    safeGetLine(em, MINEMAIL, user::MAXSTR);
    const regex pattern(R"(\b[A-Za-z0-9_][A-Za-z0-9._-]*[A-Za-z0-9]@[A-Za-z0-9-]+(?:\.[A-Za-z0-9-]+)*(?:\.[A-Z|a-z]{2,}\b))");
    //now check if the email matches the pattern and return it
    return regex_match(em, pattern);
}

bool Battleship::checkPw(string& pw) {
    
    //initialize all to false
    bool valid = false;
    bool upper = false;
    bool lower = false; 
    bool num   = false;
    //Get password and verify password length
    safeGetLine(pw, MINPWORD, user::MAXSTR);
    //verify we have upper, lower, and number - check all at once!
    for(char ch : pw){
        if(isupper(ch)){ upper = true; }
        if(islower(ch)){ lower = true; }
        if(isdigit(ch)){ num   = true; }
    }
    //we met all criteria, set to true
    if(upper && lower && num) { valid = true; }
    //missing something
    if(!upper) { cout << "Password must contain an upper case letter. " << endl; }
    if(!lower) { cout << "Password must contain a lower case letter. "; }
    if(!num)   { cout << "Password must contain a number. "; }
    //send it back baby
    return valid;
}

bool Battleship::verify(string em, string pw) {
    
    bool valid = false;
    int pos = -1;

    //open the database file
    this->accounts.open();

    //check all records for em
    pos = this->accounts.find(em);
    if (pos > -1) {
        //user found - check if password matches
        User user;
        this->accounts.get(pos, &user);
        if (user.getPword() == pw) {
            valid = true;
        }
    }

    this->accounts.close();
    
    return valid;
}
bool Battleship::Rules(){
     //Declaring variables
    fstream txt;
    char c = ' ';
    string str;
    //Clearing terminal and opening up text file and displaying rules of game
    system("cls");
    txt.open("Rules.txt", ios::in);
    while (getline(txt, str)) {
        cout << str << endl;
    }
    //closing file
    txt.close();
    //Prompting User to return to main menu or exit game
    cout << endl << endl << "Would you like to quit or return to main menu" << endl;
    cout << endl << "1 = Quit Game" << endl << "2 = Main Menu " << endl << "Choose: ";
    cin >> c;
    if (toupper(c) == '1') {
        return true;
    }
    //returning to main menu and clear terminal
    else if (toupper(c) == '2') {
        system("cls"); return false; 
    }
    else {
        return false;
    }
}

// TODO: --> MOVE THIS TO Game.cpp
//void Battleship::play(){
//    // Create two game boards, one for each player
//    Player* p1;
//    Player* p2;
//    int row, col;
//    char letter;
//
//    // Display player 1's board after ship placement
//    cout << "Player 1's Board before ship placement:" << endl;
//    p1.displayBoard();
//    
//    // Prompt player 1 to place ships on the board
//    cout << "Player 1, please place your ships:" << endl;
//    p1.promptShipPlacement();
//
//    // Display player 1's board after ship placement
//    cout << "Player 1's Board after ship placement:" << endl;
//    p1.displayBoard();
//    
//    // Prompt player 2 to place ships on the board
//    cout << "Player 2, please place your ships:" << endl;
//    p2.promptShipPlacement();
//
//    // Display player 2's board after ship placement
//   cout << "Player 2's Board after ship placement:" << endl;
//    p2.displayBoard();
//
//    while(p2.getUnsunk() > 0 || p1.getUnsunk() > 0){
//        
//        cout << "Commence attack. Enter row and col coordinates:" << endl;
//        cin >> letter >> row;
//        col = letter - 65;
//        p1.attackCell(row, col, p2);
//        p1.displayShots();
//    }
//}
void Battleship::Quit() {
    //making the user wait specific time before quit program for added realism
    cout << endl << "Exiting Battleship. Farewell Sailor!" << endl;
    //thread - duration function for 3 seconds
    chrono::seconds duration(3);
    //this_thread::sleep_for(duration);
}