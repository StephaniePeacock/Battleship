/* 
 * File:   Battleship.cpp
 * Authors: Anthony Bliss, Steven Contreres, Leoncio Hermosillo, 
 *          Isaiah Lopez, Carlos Moreno, Stephanie Peacock, Marco Reyes,  
 *          Matthew Rodriguez, Michael Hawara, Allen Yang, Hannes Ziegler  
 *
 * Created on April 19, 2024, 6:39 PM
 * Purpose: WIP implementation for all classes
 */

#include "Battleship.h"

// <editor-fold defaultstate="collapsed" desc="#Player.cpp">
Player::Player() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = EMPTY_CELL;
            shots[i][j] = EMPTY_CELL;
        }
    }
    shipCounts['C'] = 1; // Carrier
    shipCounts['B'] = 2; // Battleship
    shipCounts['D'] = 3; // Destroyer
    shipCounts['S'] = 3; // Submarine
    shipCounts['P'] = 4; // Patrol Boat
    unsunk = 0;
}

Player::~Player() {
}

void Player::setBoard(int row, int col, const char c) {
    board[row][col] = c;
}

void Player::setShots(int row, int col, const char c) {
    shots[row][col] = c;
}

int Player::convToInt(string input) // done
{
    char row = input[0];
    int col = (input[1] - '0') - 1;
    int total = 0;

    // if player chooses column 10, add 9 to col -- col only checks first digit initially
    if ((input[1] - '0') == 1 && (input[2] - '0') == 0)
        col += 9;

    switch (row) {
            // A through J for 10x10 grid
        case 'A':
        case 'a':
            total += col;
            break;
        case 'B':
        case 'b':
            total = 10 + col;
            break;
        case 'C':
        case 'c':
            total = 20 + col;
            break;
        case 'D':
        case 'd':
            total = 30 + col;
            break;
        case 'E':
        case 'e':
            total = 40 + col;
            break;
        case 'F':
        case 'f':
            total = 50 + col;
            break;
        case 'G':
        case 'g':
            total = 60 + col;
            break;
        case 'H':
        case 'h':
            total = 70 + col;
            break;
        case 'I':
        case 'i':
            total = 80 + col;
            break;
        case 'J':
        case 'j':
            total = 90 + col;
            break;
        default:
            total = -1;
    }

    // 99 is the only square where horizontal/vertical ships cannot be placed with min ship size of 2
    if (total >= 99)
        total = -1;

    return total;
}

// Function to display the current state of the board

void Player::displayBoard() {
    cout << "   A B C D E F G H I J" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << i << "  ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// display shots taken (based on opponent's board)

void Player::displayShots() {
    cout << "   A B C D E F G H I J" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << i << "  ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << shots[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if a ship can be placed at the given coordinate

bool Player::isValidPlacement(int row, int col, int size, char direction) {
    if (!isValidCoordinate(row, col) || (direction != 'H' && direction != 'V'))
        return false;

    if (direction == 'H') {
        if (col + size - 1 >= BOARD_SIZE)
            return false;
        for (int j = col; j < col + size; ++j) {
            if (board[row][j] == SHIP_CELL)
                return false;
        }
    } else { // direction == 'V'
        if (row + size - 1 >= BOARD_SIZE)
            return false;
        for (int i = row; i < row + size; ++i) {
            if (board[i][col] == SHIP_CELL)
                return false;
        }
    }

    return true;
}

// Function to place a ship on the board

bool Player::placeShip(int row, int col, int size, char direction, char shipType) {
    if (shipCounts[shipType] <= 0 || !isValidPlacement(row, col, size, direction)) {
        cout << "Invalid placement!" << endl;
        return false;
    }

    if (direction == 'H') {
        for (int j = col; j < col + size; ++j) {
            setBoard(row, j, SHIP_CELL);
            unsunk++;
        }
    } else { // direction == 'V'
        for (int i = row; i < row + size; ++i) {
            setBoard(i, col, SHIP_CELL);
            unsunk++;
        }
    }

    shipCounts[shipType]--;
    //    displayBoard(); // Display the board after each placement
    return true;
}

// Function to prompt the user to place ships on the board

void Player::promptShipPlacement() {
    char shipTypes[] = {'C', 'B', 'D', 'S', 'P'};
    for (char shipType : shipTypes) {
        int size = shipType == 'C' ? 5 : shipType == 'B' ? 4
                : shipType == 'D' ? 3
                : shipType == 'S' ? 3
                : 2;
        cout << "Placing " << size << "-unit " << shipType << " ship." << endl;
        while (true) {
            int location;
            string input;
            char letter;
            char direction;
            cout << "Enter starting coordinates. (Ex. B4)" << endl;
            cin >> input;
            cout << "Enter direction (H for horizontal, V for vertical): ";
            cin >> direction;
            location = Player::convToInt(input);
            int row = location / 10, col = location % 10;
            if (placeShip(row, col, size, direction, shipType)) {
                cout << "Ship placed successfully!" << endl;
                break;
            } else {
                cout << "Invalid coordinates or ship placement. Try again." << endl;
            }
        }
    }
}

// Function to attack a cell on the opponent's board

void Player::attackCell(int row, int col, Player *enemy) {
    if (enemy->board[row][col] == SHIP_CELL) {
        cout << "Hit!" << endl;
        enemy->setBoard(row, col, HIT_CELL);
        setShots(row, col, HIT_CELL);
    } else {
        cout << "Miss!" << endl;
        enemy->setBoard(row, col, MISS_CELL);
        setShots(row, col, MISS_CELL);
    }
}

void Player::serialize(stringstream &buffer, int &size) {
    /* --Player serialization binary storage structure--
     * short unsigned int:  type of object (Player=0, Comp=1)
     * int:                 size of board
     * char[board size]:    char for each item in board array
     * char[board size]:    char for each item in shots array
     * int:                 shipCounts map count
     * char & int pars:     first key (char) then value (int)
     *                        for each pair in map
     * int:                 unsunk integer value
     */

    cout << "SERIALIZING...\n"; //DEBUG

    // Store object type to aid in deserialization
    short unsigned int type = static_cast<short unsigned int>(TYPE);
    buffer.write(reinterpret_cast<char*>(&type), sizeof (type));
    size += sizeof (type);

    //// Store each of the arrays (board, shots)

    // Store size of the board.
    int board_size = BOARD_SIZE;
    buffer.write(reinterpret_cast<char*>(&board_size), sizeof (board_size));

    // Store board
    for (int r = 0; r < board_size; r++) {
        buffer.write(board[r], sizeof (board[r]));
    }
    // Store shots
    for (int r = 0; r < board_size; r++) {
        buffer.write(shots[r], sizeof (shots[r]));
    }
    size += board_size * board_size * sizeof (char) * 2;

    //// Store unordered_map (shipCounts)

    // Store size of unordered_map
    int map_count = shipCounts.size();
    buffer.write(reinterpret_cast<char*>(&map_count), sizeof (map_count));

    // Store each key, value pair
    for (const pair<char, int> &kv : shipCounts) {
        //        cout << kv.first << " : " << kv.second << "\n";  //DEBUG
        buffer.write(reinterpret_cast<const char*>(&kv.first), sizeof (kv.first));
        buffer.write(reinterpret_cast<const char*>(&kv.second), sizeof (kv.second));
    }
    size += map_count * (sizeof (char) + sizeof (int));

    // Sore unsunk integer value
    buffer.write(reinterpret_cast<char*>(&unsunk), sizeof (unsunk));
    size += sizeof (unsunk);

    cout << "FINISHED SERIALIZING\n"; //DEBUG
}

void Player::deserialize(stringstream& buffer) {

    cout << "DESERIALIZING...\n"; //DEBUG

    int board_size, map_count;

    //// Read each of the arrays (board, shots)

    // Read size of the board.
    buffer.read(reinterpret_cast<char*>(&board_size), sizeof (board_size));
    // Read board
    for (int r = 0; r < board_size; r++) {
        for (int c = 0; c < board_size; c++) {
            buffer.read(reinterpret_cast<char *>(&board[r][c]), sizeof (char));
        }
    }
    displayBoard(); //DEBUG
    // Read shots
    for (int r = 0; r < board_size; r++) {
        for (int c = 0; c < board_size; c++) {
            buffer.read(reinterpret_cast<char*>(&shots[r][c]), sizeof (char));
        }
    }

    //// Read unordered_map (shipCounts)
    // Read size of unordered_map
    buffer.read(reinterpret_cast<char*>(&map_count), sizeof (map_count));
    // Read each key, value pair
    char key;
    int val;
    for (int i = 0; i < map_count; i++) {
        buffer.read(reinterpret_cast<char*>(&key), sizeof (key));
        buffer.read(reinterpret_cast<char*>(&val), sizeof (val));
        shipCounts[key] = val;
    }

    // Read unsunk integer value
    buffer.read(reinterpret_cast<char*>(&unsunk), sizeof (unsunk));

    cout << "FINISHED DESERIALIZING\n"; //DEBUG
}// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="#Comp.cpp">

Comp::Comp() : Player() {
    this->smart = false;
}

Comp::Comp(bool smart) : Player() {
    this->smart = smart;
}

void Comp::serialize(stringstream& buffer, int&) {
    //TODO
}

void Comp::deserialize(stringstream& file) {
    //TODO
}// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="#Game.cpp">

Game::Game(Player *p1, Player *p2, string uid) {
    this->p1 = p1;
    this->p2 = p2;
    safeCStrNCpy(this->uid, uid, MAXUID);
    this->turn = false;
    this->clr = false;
}

Game::~Game() {
    // Sometimes we allocate new memory, conditionally clear it
    if (clr) {
        delete p1;
        p1 = nullptr;
        delete p2;
        p2 = nullptr;
    }
}

/// @brief Update whose turn it is

void Game::doTurn() {
    turn = !turn;
}

void Game::play() {
    string input;
    int row, col;
    char letter;

    // Display player 1's board after ship placement
    cout << "Player 1's Board before ship placement:" << endl;
    p1->displayBoard();

    // Prompt player 1 to place ships on the board
    cout << "Player 1, please place your ships:" << endl;
    p1->promptShipPlacement();

    // Display player 1's board after ship placement
    cout << "Player 1's Board after ship placement:" << endl;
    p1->displayBoard();

    // Prompt player 2 to place ships on the board
    cout << "Player 2, please place your ships:" << endl;
    p2->promptShipPlacement();

    // Display player 2's board after ship placement
    cout << "Player 2's Board after ship placement:" << endl;
    p2->displayBoard();

    while (p2->getUnsunk() > 0 || p1->getUnsunk() > 0) {

        cout << "Commence attack. Enter row and col coordinates:" << endl;
        cin >> input;
        int location = Player::convToInt(input);
        int row = location / 10;
        int col = location % 10;
        col = letter - 65;
        p1->attackCell(row, col, p2);
        p1->displayShots();
    }
}

Player* Game::getPlayer1() {
    return this->p1;
}

Player* Game::getPlayer2() {
    return this->p2;
}

void Game::serialize(stringstream& buffer) {
    /* --Game serialization binary storage structure--
     * char[MAXUID]:        Unique identifier (UID) of game
     *                      - Used to find game
     * int:                 size (in bytes) of game
     *                      - Used for seeking
     * bool:                current turn
     * Player:              Player 1
     * Player:              Player 2
     */
    stringstream p1_buff, p2_buff;
    int p1_size = 0, p2_size = 0, game_size = 0;

    // Serialize each Player object to a buffer
    p1_buff.seekp(0L, std::ios::end);
    p1->serialize(p1_buff, p1_size);
    p2_buff.seekp(0L, std::ios::end);
    p2->serialize(p2_buff, p2_size);

    // Store the unique identifier of the game
    buffer.write(reinterpret_cast<char*>(&uid), sizeof (uid));

    // Store the size of game (used for seeking)
    game_size = sizeof (bool) + p1_size + p2_size;
    cout << "WRITE GAME SIZE: " << game_size << "\n"; //DEBUG
    buffer.write(reinterpret_cast<char*>(&game_size), sizeof (game_size));

    // Store the current turn
    buffer.write(reinterpret_cast<char*>(&turn), sizeof (turn));

    // Store Player 1
    string p1_str = p1_buff.str();
    buffer.write(p1_str.c_str(), p1_str.size());
    // Store Player 2
    string p2_str = p2_buff.str();
    buffer.write(p2_str.c_str(), p2_str.size());
}

void Game::deserialize(stringstream& buffer) {
    /* Assumes that buffer stream read position is already set.
     *
     * Deserialize each polymorphic type by calling its own
     * deseralize method. Each one knows how to correctly load
     * its type's data from buffer.
     */

    short unsigned int type_val;
    PlayerType type;

    // Read the current turn
    buffer.read(reinterpret_cast<char*>(&turn), sizeof (turn));
    cout << "READ CURRENT TURN: " << turn << "\n"; //DEBUG

    // Conditionally clear old allocated memory for this->p1 and this->p2
    if (clr) {
        delete this->p1;
        this->p1 = nullptr;
        delete this->p2;
        this->p2 = nullptr;
        cout << "FREED UP MEMORY\n"; //DEBUG
    } else {
        this->clr = true; // If not already true, set to true (clear next time)
    }

    //// Deserialize p1 (Player 1)
    cout << "PROCESSING PLAYER 1...\n"; //DEBUG

    // Read the Player object type
    buffer.read(reinterpret_cast<char*>(&type_val), sizeof (type_val));
    type = static_cast<PlayerType>(type_val);

    cout << "TYPE: " << static_cast<int>(type) << "\n";

    // get new p1; Use appropriate serialization method for type
    switch (type) {
        case PlayerType::PLAYER:
        {
            Player* p1 = new Player();
            p1->deserialize(buffer);
            this->p1 = p1;
            break;
        }
        case PlayerType::COMP:
        {
            Comp* p1 = new Comp();
            p1->deserialize(buffer);
            this->p1 = p1;
            break;
        }
    }
    this->p1->displayBoard();
    this->p1->displayShots();
    cout << "FINISHED PROCESSING PLAYER 1\n"; //DEBUG

    //// Deserialize p2 (Player 2)
    cout << "PROCESSING PLAYER 2...\n"; //DEBUG

    // Read the Player object type
    buffer.read(reinterpret_cast<char*>(&type_val), sizeof (type_val));
    type = static_cast<PlayerType>(type_val);

    cout << "TYPE: " << static_cast<int>(type) << "\n";

    // get new p2; Use appropriate serialization method for type
    switch (type) {
        case PlayerType::PLAYER:
        {
            Player* p2 = new Player();
            p2->deserialize(buffer);
            this->p2 = p2;
            break;
        }
        case PlayerType::COMP:
        {
            Comp* p2 = new Comp();
            p2->deserialize(buffer);
            this->p2 = p2;
            break;
        }
    }
    this->p2->displayBoard();
    this->p2->displayShots();
    cout << "FINISHED PROCESSING PLAYER 2\n"; //DEBUG
}// </editor-fold>

// #GamesDB.cpp
GamesDB::GamesDB() {
}

// <editor-fold defaultstate="collapsed" desc="#User.cpp">
//Default User Constructor

User::User() {
    email[0] = '\0';
    pword[0] = '\0';
    isadmin = false;
    info.win = 0;
    info.loss = 0;
    //add Game default
}

//for registering a new user

User::User(const string em, const string pw, const bool adm) {
    safeCStrNCpy(this->email, em, MAXSTR);
    safeCStrNCpy(this->pword, pw, MAXSTR);
    this->isadmin = adm;
    this->info = Stats{0, 0};
    //add Game default
}

//for loading an existing user

User::User(const string em, const string pw, Stats s, const bool adm) {
    safeCStrNCpy(email, em, MAXSTR);
    safeCStrNCpy(pword, pw, MAXSTR);
    isadmin = adm;
    info.win = s.win;
    info.loss = s.loss;
    //add Game object
}

void User::setEmail(const string em) {
    safeCStrNCpy(this->email, em, MAXSTR);
}

const string User::getEmail() {
    return this->email;
}

void User::setPword(const string pw) {
    safeCStrNCpy(this->pword, pw, MAXSTR);
}

const string User::getPword() {
    return this->pword;
}

const bool User::isAsmin() {
    return this->isadmin;
}

void User::setAdmin(const bool adm) {
    this->isadmin = adm;
}

string User::newGameUID() {
    // Get timestamp in milliseconds since epoch
    uint64_t now = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch()
            ).count();
    return email + (string) "_" + to_string(now);
}

void User::display() const {
    cout << "Email: " << this->email << "\n";
    cout << "Password: " << this->pword << "\n";
    cout << "Wins: " << this->info.win << "\n";
    cout << "Losses: " << this->info.loss << "\n";
}
//Menu options for the non-administrative player



void User::saveGame(Game& game) {

}// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="#AccountsDB.cpp">

AccountsDB::AccountsDB() {
    this->fname = "";
}

AccountsDB::AccountsDB(string fname) {
    this->fname = fname;
}

void AccountsDB::open() {
    file.open(fname, ios::binary | ios::in | ios::out);
    if (file.fail()) {
        cout << "Error opening file: " << fname << "\n";
    }
}

void AccountsDB::close() {
    file.close();
    if (file.fail()) {
        cout << "Error closing file: " << fname << "\n";
    }
}

void AccountsDB::createDB(string fname) {

    // check file existence, createDB if doesn't exist
    fstream file;
    file.open(fname, ios::in | ios::binary);
    if (!file) {
        file.close();
        file.open(fname, ios::out | ios::binary);
    } else {
        cout << "File \"" << fname << "\" already exists.\n";
    }
    file.close();
}

void AccountsDB::deleteDB(string fname) {
    if (remove(fname.c_str()) != 0) {
        cout << "   Failed to delete file \"" << fname << "\".\n";
    } else {
        cout << "   Successfully deleted file \"" << fname << "\".\n";
    }
}

int AccountsDB::count() {

    // Get size of file
    int fbytes = size();

    // Get size of record
    int rbytes = sizeof (User);

    // Calculate and return number of records in database
    return fbytes / rbytes;
}

long int AccountsDB::size() {
    file.seekg(0L, ios::end);
    return file.tellg();
}

int AccountsDB::find(string email) {
    int i = 0;
    int pos = -1;
    int end = count();
    User current;
    file.seekg(0L, ios::beg);
    //    cout << "Searching for " << email << "\n";  //DEBUG

    while (i < end) {
        //        cout << "Searching user #" << i << "\n";  //DEBUG
        file.read(reinterpret_cast<char*>(&current), sizeof (User));
        if (current.getEmail() == email) { //account found
            pos = i;
            break;
        }
        i++;
    }
    return pos;
}

void AccountsDB::add(const User* user) {
    file.seekp(0L, ios::end);
    file.write(reinterpret_cast<const char*>(user), sizeof (User));
    file.flush();
}

void AccountsDB::get(int pos, User* user) {
    long int cur = pos * sizeof (User);
    file.seekg(cur, ios::beg);
    file.read(reinterpret_cast<char*>(user), sizeof (User));
}

void AccountsDB::getAll(User* users) {
    int end = count();
    file.seekg(0L, ios::beg);
    for (int i = 0; i < end; i++) {
        file.read(reinterpret_cast<char*>(&users[i]), sizeof (User));
    }
}

void AccountsDB::set(int pos, const User& user) {
    long int cur = pos * sizeof (User);
    this->open();
    
    
    file.seekp(cur, ios::beg);
    file.write(reinterpret_cast<const char*>(&user), sizeof (User));
    // Check for errors after writing
    if (file.fail()) {
        cout << "Error writing to file: " << fname << endl;
    }
    this->close();
    file.flush();
}

void AccountsDB::setAll(User* records, int cnt) {

    delAll();
    file.seekp(0L, ios::beg);
    for (int i = 0; i < cnt; i++) {
        file.write(reinterpret_cast<char*>(&records[i]), sizeof (User));
    }

    file.flush();
}

void AccountsDB::del(int pos) {
    // Start position of chunk
    long int sbytes = pos * sizeof (User); //Start byte of record to del.
    long int ebytes = size(); //Size (bytes) of file
    long int rbytes = sizeof (User); //Size (bytes) of record
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
    delAll();

    // Reconstruct file contents (without deleted record)
    file.seekp(0L, ios::end);
    file.write(buffer_a, sbytes);
    file.write(buffer_b, cbytes);
    // Check for errors after writing
    if (file.fail()) {
        cout << "Error writing to file: " << fname << endl;
    }
    file.flush();
}
// FAILED ATTEMPT: This leaves the file the same size it was before...
// NOTE: Keeping this around in case I have time to attempt to make this work later...
///// @brief Delete the record at the given index in the database.
///// @param pos The index position of the user record to delete.
//void AccountsDB::del(int pos)
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

void AccountsDB::delAll() {

    // Check if stream is open, close if open, remember initial state
    bool opn = false;
    if (file.is_open()) {
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

void AccountsDB::display() {
    int cnt = count();
    //    cout << "COUNT: " << cnt << "\n\n";  //DEBUG
    if (cnt > 0) {
        User record;
        file.seekg(0L, ios::beg);
        for (int i = 0; i < cnt; i++) {
            file.read(reinterpret_cast<char*>(&record), sizeof (User));
            record.display();
        }
    } else {
        cout << "There are no users in the database\n";
    }


}// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="#Battleship.cpp">

Battleship::Battleship() {
    AccountsDB::createDB(DBPATH);
    this->accounts = AccountsDB(DBPATH);
}

void Battleship::loading() {
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
        choice = getSingleChar(); // Get char safely
        switch (choice) {
            case '1':
                login();
                break;
            case '2':
                reg();
                break;
            case '3':
                rules();
                break;
            case 'a': //FOR DEBUG ONLY, display all users
                this->accounts.open();
                this->accounts.display();
                this->accounts.close();
                break;
            case 'l': //FOR DEBUG ONLY, quickly login to test user account and play game
            {
                User user;
                this->accounts.open();
                this->accounts.get(0, &user);
                this->accounts.close();
                cout << "LOGGING IN AS \n";
                user.display(); //DEBUG
                cout << "\n";
                userMenu(user);
                break;
            }
                //        case 'm': { //FOR DEBUG ONLY, make an admin user lol
                //            User user = User("admin@org.com", "AdminUser1", true);
                //            this->accounts.open();
                //            this->accounts.add(&user);
                //            this->accounts.close();
                //            break;
                //        }
            case 'g':
            { //FOR DEBUG ONLY, test storing Game object in binary file
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
                buffer.read(reinterpret_cast<char*>(c_uid), sizeof (c_uid));
                cout << "READ GAME UID: " << c_uid << "\n";

                int gsize = 0;
                buffer.read(reinterpret_cast<char*>(&gsize), sizeof (gsize));
                cout << "READ GAME SIZE: " << gsize << "\n";

                cout << "DESEREALIZING GAME...\n";
                game.deserialize(buffer);
                cout << "SUCCESSFULLY DESERIALIZED!\n";

                cout << "PLAYER 1\n";
                Player* p1n = game.getPlayer1();
                p1n->displayBoard();
                p1n->displayShots();

                cout << "PLAYER 2\n";
                Player* p2n = game.getPlayer2();
                p2n->displayBoard();
                p2n->displayShots();

                break;
            }
            case '4':
                quit = true;
                break;
            default:
                cout << "Aye, matey! That be no valid course o’ action. Sing a new tune and try again!\n";
                break;
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
    safeGetLine(e, MAXSTR);

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
    safeGetLine(p, MAXSTR);

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

    userMenu(user);

    //return to main menu
}

void Battleship::reg() {
    string e, p;
    cout << "Ahoy Captain! Ready to enlist?\n";

    // Get validated e-mail
    cout << "Enter your email address: ";
    while (!checkEm(e)) {
        cout << "Invalid email, please re-enter: ";
    }

    // Get validated password
    cout << "Enter yer top secret code: ";
    while (!checkPw(p)) {
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
    safeGetLine(em, MINEMAIL, MAXSTR);
    const regex pattern(R"(\b[A-Za-z0-9_][A-Za-z0-9._-]*[A-Za-z0-9]@[A-Za-z0-9-]+(?:\.[A-Za-z0-9-]+)*(?:\.[A-Z|a-z]{2,}\b))");
    //now check if the email matches the pattern and return it
    return regex_match(em, pattern);
}

bool Battleship::checkPw(string& pw) {

    //initialize all to false
    bool valid = false;
    bool upper = false;
    bool lower = false;
    bool num = false;
    //Get password and verify password length
    safeGetLine(pw, MINPWORD, MAXSTR);
    //verify we have upper, lower, and number - check all at once!
    for (char ch : pw) {
        if (isupper(ch)) {
            upper = true;
        }
        if (islower(ch)) {
            lower = true;
        }
        if (isdigit(ch)) {
            num = true;
        }
    }
    //we met all criteria, set to true
    if (upper && lower && num) {
        valid = true;
    }
    //missing something
    if (!upper) {
        cout << "Password must contain an upper case letter. " << endl;
    }
    if (!lower) {
        cout << "Password must contain a lower case letter. ";
    }
    if (!num) {
        cout << "Password must contain a number. ";
    }
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

bool Battleship::rules() {
    //Declaring variables
    fstream txt;
    char c = ' ';
    string str;
    //Clearing terminal and opening up text file and displaying rules of game
    // system("cls");
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
    }        //returning to main menu and clear terminal
        //else if (toupper(c) == '2') {
        //     system("cls"); return false; 
        // }
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
    //chrono::seconds duration(3);
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
    this->accounts.open();
    int pos = this->accounts.find(email);  //for overwriting the user data
    this->accounts.close();
    
    //Switch case within do-while loop for user submenu options
//    system("cls");
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
        //        cout << "New info to be saved:\n";
        //        user.display();
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
                    this->accounts.open();
                    this->accounts.del(pos);
                    this->accounts.close();
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

void Battleship::gameMenu(User user) {
    //Declare all Variables Here
    int choice;
    bool quit = false;
    //Switch case within do-while loop for Game menu
//    system("cls");
    do {
        cout << "[1] New Campaign\n[2] Load Campaign\n[3] Go Back\n";
        getNumeric<int>(choice);
        switch (choice) {
            case 1:
                cout << "Launching a new game";
                break;
            case 2:
                cout << "Recovering previous game";
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



// </editor-fold>
