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
//    cout << "Loading please wait...";
//    chrono::seconds duration(3);
    /*
     * if you reached this error then netbeans does not support this_thread function from thread library.
     * function would pause game for as long as we want, perfect for loading games, simulation connecting to and online server etc..
     * can comment out and I will try to find a work around
     */
//    this_thread::sleep_for(duration);
//    system("cls");
    cout << "8 8888888o        .8.      88888 88888  88888 88888  8 88       8 888888   d888888o.   8 88      88  8 88  8 88888888o" << endl;
    cout << "8 88    `88.      .88.         8 88        8 88      8 88       8 88      .`88:' `88.  8 88      88  8 88  8 888    `88." << endl;
    cout << "8 88     `88      :888.        8 88        8 88      8 88       8 88      8.`88.   Y8  8 88      88  8 88  8 888     `88" << endl;
    cout << "8 88     ,88     . `888.       8 88        8 88      8 88       8 88      `8.`88.      8 88      88  8 88  8 888     ,88" << endl;
    cout << "8 88.   ,88'    .8. `888.      8 88        8 88      8 88       8 888888   `8.`88.     8 88      88  8 88  8 888.   ,88'" << endl;
    cout << "8 88888888     .8`8. `888.     8 88        8 88      8 88       8 88        `8.`88.    8 88      88  8 88  8 88888888P'" << endl;
    cout << "8 88    `88.  .8' `8. `888.    8 88        8 88      8 88       8 88         `8.`88.   8 8888888888  8 88  8 888" << endl;
    cout << "8 88      88 .8'   `8. `888.   8 88        8 88      8 88       8 88     8b   `8.`88.  8 88      88  8 88  8 888" << endl;
    cout << "8 88    ,88'.888888888. `888.  8 88        8 88      8 88       8 88     `8b.  ;8.`88  8 88      88  8 88  8 888" << endl;
    cout << "8 8888888P .8'       `8. `888. 8 88        8 88      8 8888888  8 8888888 `Y88P ,88P'  8 88      88  8 88  8 888" << endl;
}
void Battleship::main() {
    //Declare all Variables Here
    char choice;
    bool quit = false;
    //Switch case within do-while loop to start the game
    loading();
    do {
        cout << endl << "Main Menu" << endl;
        cout << "[1] Login\n"
                "[2] Register\n"
                "[3] Rules\n"
                "[4] Exit\n" << ">> ";
        choice = getSingleChar();  // Get char safely
        switch (choice)
        {
        case '1':
            login();break;
        case '2':
            reg();break;
        case '3':
           quit = rules(); break;
        case 'a':  //FOR DEBUG ONLY, display all users
            this->accounts.display();
            break;
        case 'l':  //FOR DEBUG ONLY, quickly login to test user account and play game
        {   
            User user;
            this->accounts.get(0, &user);
            cout << "LOGGING IN AS \n";
            user.display();  //DEBUG
            cout << "\n";
            userMenu(user);
            break;
        }
//        case 'm': { //FOR DEBUG ONLY, make an admin user lol
//            
//            User user = User("admin@org.com", "AdminUser1", true);
//            this->accounts.delAll();
//            this->accounts.add(&user);
//            break;
//        }
        case 'g': {  //FOR DEBUG ONLY, test storing Game object in binary file
            Player p1 = Player();
            Player p2 = Player();
            User user;
            this->accounts.get(1, &user);
            string uid = "hannes@mail.com_1714321083707";
            
            // Create GamesDB if it doesn't already exist
            GamesDB::createDB(user::GAMESDBPATH);
            GamesDB gamesdb = GamesDB(user::GAMESDBPATH);
            
            gamesdb.open();
            gamesdb.list();
            gamesdb.close();
            
//            cout << "GAME UID: " << uid << "\n";
//            
//            // Do some stuff to modify game state
//            p1.placeShip(2, 8, 5, 'V', 'C');
//            p1.placeShip(5, 3, 3, 'H', 'S');
//            p2.attackCell(3, 3, &p1);
//            p2.attackCell(5, 3, &p1);
//            cout << "PLAYER 1 BOARD:\n";
//            p1.displayBoard();
//            cout << "PLAYER 1 SHOTS:\n";
//            p1.displayShots();
//            cout << "PLAYER 2 BOARD:\n";
//            p2.displayBoard();
//            cout << "PLAYER 2 SHOTS:\n";
//            p2.displayShots();
//            
//            Game game = Game(&p1, &p2, uid);           
//            
//            // Add some more games for testing
//            Player pa1 = Player();
//            Comp pa2 = Comp();
//            Game ga = Game(&pa1, &pa2, "hannes@mail.com_1714321083709");
//            
//            Comp pb1 = Comp();
//            Comp pb2 = Comp();
//            Game gb = Game(&pb1, &pb2, "hannes@mail.com_1714321083712");
//            
//            Comp pc1 = Comp();
//            Player pc2 = Player();
//            Game gc = Game(&pc1, &pc2, "hannes@mail.com_1714321083727");
//            
//            // Save a games
//            gamesdb.open();
//            gamesdb.save(ga);
//            gamesdb.save(gb);
//            gamesdb.save(game);
//            gamesdb.save(gc);
//            gamesdb.list();
//            gamesdb.close();
//            
//            // Load a game
//            Game game_load = Game(uid);
//            gamesdb.open();
//            gamesdb.load(game_load);
//            gamesdb.del("hannes@mail.com_1714321083709");
//            gamesdb.del("hannes@mail.com_1714321083707");
//            gamesdb.del("hannes@mail.com_1714321083727");
//            gamesdb.list();
//            gamesdb.close();
            
//            stringstream buffer;
//            buffer.seekp(0L, ios::end);
//            cout << "SEREALIZING GAME...\n";
//            game.serialize(buffer);
//            cout << "SUCCESSFULLY SERIALIZED GAME!\n";
//            buffer.seekg(0L, ios::beg);
//            cout << "SET CURSOR TO BEGINNING\n";
//            
//            char c_uid[102];
//            buffer.read(reinterpret_cast<char*>(c_uid), sizeof(c_uid));
//            cout << "READ GAME UID: " << c_uid << "\n";
//            
//            int gsize = 0;
//            buffer.read(reinterpret_cast<char*>(&gsize), sizeof(gsize));
//            cout << "READ GAME SIZE: " << gsize << "\n";
//            
//            cout << "DESEREALIZING GAME...\n";
//            game.deserialize(buffer);            
//            cout << "SUCCESSFULLY DESERIALIZED!\n";
//            
//            cout << "PLAYER 1\n";
//            Player* p1n = game.getP1();
//            p1n->displayBoard();
//            p1n->displayShots();
//            
//            cout << "PLAYER 2\n";
//            Player* p2n = game.getP2();
//            p2n->displayBoard();
//            p2n->displayShots();
            
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
    pos = this->accounts.find(e);
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
    this->accounts.get(pos, &user);
    
    //Give admin the admin menu first, users go right to user menu
        if(!user.isAdmin()){
        userMenu(user);
    } else {
        int choice;
        bool quit = false;
        do{
            cout << "[1] Admin Menu\n"
                    "[2] User  Menu\n"
                    "[3] Logout.";
            getNumeric<int>(choice);
            switch(choice){
                case 1:
                    adminMenu(user);
                    break;
                case 2: 
                    userMenu(user);
                    break;
                default: quit = true;
                break;
            }
        } while (!quit);
        
        
    }
    
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
    this->accounts.add(&usr);
    
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
    //check all records for em - opens inside find
    pos = this->accounts.find(em);
    if (pos > -1) {
        //user found - check if password matches
        User user;
        this->accounts.get(pos, &user);
        if (user.getPword() == pw) {
            valid = true;
        }
    }
    return valid;
}

bool Battleship::rules(){
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

void Battleship::Quit() {
    //making the user wait specific time before quit program for added realism
    cout << endl << "Exiting Battleship. Farewell Sailor!" << endl;
    //thread - duration function for 3 seconds
    chrono::seconds duration(3);
    //this_thread::sleep_for(duration);
}

void Battleship::userMenu(User& user) {
    //Declare all Variables Here
    int choice;
    bool quit = false;
    //Switch case within do-while loop for user options
//    system("cls");
    do {
        cout << "[1] Account Info\n[2] Play Game\n[3] Update Account\n[4] Logout\n";
        getNumeric<int>(choice);
        switch (choice) {
            case 1:
                user.display();
                break;
            case 2:
                gameMenu(user);
                break;
            case 3:
                if(!acctMenu(user)){
                    quit = true;
                }
                break;
            case 4:
                quit = true;
                break;
            default:
                cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";
                break;
        }
    } while (!quit);
    //returning to main menu and clearing the terminal
    cout << "Logging out...bye world" << endl;
//    system("cls");
}

bool Battleship::acctMenu(User& user) {
    //Declare all Variables Here
    int choice, sure;
    string e, p;
    bool quit = false;
    string email(user.getEmail());
    int pos = this->accounts.find(email);  //for overwriting the user data

    do {
        cout << "[1] Change email\n"
                "[2] Update Password\n"
                "[3] Delete Account\n"
                "[4] Go Back\n";
        getNumeric<int>(choice);
        switch (choice) {
            case 1: {
                // Get validated e-mail
                cout << "Enter your email address: "; 
                while (!checkEm(e)) {
                    cout << "Invalid email, please re-enter: ";
                }
                const char* em = e.c_str();
                user.setEmail(em);
                // Store updated account in database
                this->accounts.set(pos,user);
                cout << "Email has been updated." << endl; 
                break; }
            case 2: {
                cout << "Enter yer top secret code: ";
                while (!checkPw(p)) {
                    cout << "This ain't no Sunday sail, Captain! Make your code more secure!!: ";
                }
                const char* pw = p.c_str();
                user.setPword(pw);
                // Store updated account in database
                this->accounts.set(pos,user);
                cout << "Password has been updated." << endl; 
            
                break;}
            case 3: {
                //doublecheck
                cout << "Are ye sure? There's no escape from this whirlpool!\n"
                        "Enter 1 to continue, 2 to cancel.";
                getNumeric<int>(sure);
                if(sure == 1){
                    // Store updated account in database
                    this->accounts.del(pos);
                    cout << "Yer fleet has been removed!/n";
                    //go back to the main menu
                    return false;
                } else {
                    cout << "Wise choice, let's go back!" << endl;
                }
                
                break;}
            case 4:
                quit = true;
                break;
            default:
                cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";
                break;
        }
    } while (!quit);
    //account exists so
    return true;
}

void Battleship::gameMenu(User& user) {
    //Declare all Variables Here
    int choice;
    bool quit = false;
    //Switch case within do-while loop for Game menu
//    system("cls");
    do {
        cout << "[1] New Campaign\n"
                "[2] Load Campaign\n"
                "[4] Delete Campaign\n"
                "[3] Go Back\n";
        getNumeric<int>(choice);
        switch (choice) {
            case 1:
                cout << "Launching a new game\n";
                user.newGame();
                break;
            case 2:
                cout << "Loading a previous game\n";
                user.loadGame();
                break;
            case 3:
                quit = true;
                break;
            default:
                cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";
                break;
        }
    } while (!quit);
}

void Battleship::adminMenu(const User& admin){ //pass admin as const so we cant delete by accident!
        int choice;
        bool quit = false;
        do{
            cout << "[1] View All Users\n"
                    "[2] Add User\n"
                    "[3] Delete User\n"
                    "[4] Modify User\n"
                    "[5] Exit Menu\n";
            getNumeric<int>(choice);
            switch(choice){
                case 1:
                    this->accounts.display();
                    break;
                case 2: 
                    this->reg();
                    break;
                case 3: 
                    this->delUser(admin);
                    break;
                case 4: 
                    cout << "Modify User\n";
                    break;
                case 5: 
                    quit = true;
                    break;
                default: cout << "Invalid option entered." << endl;
                break;
            }
        } while (!quit);
}

void Battleship::delUser(const User admin){
    //find the position
    cout << "Enter the Captain's e-mail address: ";
    string e;
    safeGetLine(e, user::MAXSTR);
    if(e != admin.getEmail()){
        int pos = this->accounts.find(e);
        if(pos >= 0){
            //remove the user
        this->accounts.del(pos);
        cout << "User removed. Updated database:\n";
        this->accounts.display();
        }
        else {cout << "User does not exist\n";}
    } else { cout << "You cannot delete your own account.\n"; }
}