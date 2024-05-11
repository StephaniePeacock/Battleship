/*
 * File:   Game.cpp
 * Author: hanne
 *
 * Created on April 14, 2024, 1:44 PM
 */

#include "Game.h"

Game::Game(string uid) {
    safeCStrNCpy(this->uid, uid, game::MAXUID);
    this->turn = false;
    this->clr = false;
}
Game::Game(Player *p1, Player *p2, string uid)
{
    this->p1 = p1;
    this->p2 = p2;
    safeCStrNCpy(this->uid, uid, game::MAXUID);
    this->turn = false;
    this->clr = false;
}

Game::~Game()
{
    // Sometimes we allocate new memory, conditionally clear it
    if (clr) {
        delete p1;
        p1 = nullptr;
        delete p2;
        p2 = nullptr;
    }
}

string Game::getUID() {
    return this->uid;
}

Player* Game::getP1() {
    return this->p1;
}

Player* Game::getP2() {
    return this->p2;
}

/// @brief Update whose turn it is
void Game::doTurn()
{
    turn = !turn;
}
bool Game::play()
{
    // DEBUG
    // QUICKLY "PLAY" A GAME THEN SAVE
//    p1->placeShip(2, 8, 5, 'V', 'C');
//    p1->placeShip(5, 3, 3, 'H', 'S');
//    p2->attackCell(3, 3, p1);
//    p2->attackCell(5, 3, p1);
//    return true;
    // END DEBUG
    
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

    cout << "Player 1's status: " << p1->getUnsunk() << endl;
    cout << "Player 2's status: " << p2->getUnsunk() << endl;

    while (p2->getUnsunk() != 0 && p1->getUnsunk() != 0)
    {
        cout << "Commence attack. Enter coordinates (Q to quit):" << endl;
        safeGetLine(input, 4);  //No more than 3 characters allowed
        
        if (input == "Q" || input == "q") {
            char save;
            cout << "Save game before quitting? (Y/)\n";
            cout << "WARNING: Choosing (Y)es will overwrite previous save\n";
            save = getSingleChar();
            tolower(save);
            if (save == 'y') {
                return true;
            }
        }
        
        int location = Player::convToInt(input);
        int row = location / 10;
        int col = location % 10;
        
        p1->attackCell(row, col, p2);
        p1->displayShots();
        

        // Player 2 now attacks (For AI purposes)
        p2->attackCell(row, col, p1);
        p2->displayShots();
    }
    
    return false;
}

void Game::serialize(stringstream& buffer)
{
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
        
    // Store the unique identifier of the game
    buffer.write(reinterpret_cast<char*>(&uid), sizeof(uid));
    
    // Serialize each Player object to a buffer
    p1_buff.seekp(0L, std::ios::end);
    p1->serialize(p1_buff, p1_size);
    p2_buff.seekp(0L, std::ios::end);
    p2->serialize(p2_buff, p2_size);
    
    // Store the size of game (used for seeking)
    game_size = (sizeof(turn) + p1_size + p2_size);
    buffer.write(reinterpret_cast<char*>(&game_size), sizeof(game_size));
    
    // Store the current turn
    buffer.write(reinterpret_cast<char*>(&turn), sizeof(turn));
    
    // Store Player 1
    string p1_str = p1_buff.str();
    buffer.write(p1_str.c_str(), p1_str.size());
    // Store Player 2
    string p2_str = p2_buff.str();
    buffer.write(p2_str.c_str(), p2_str.size());
}

void Game::deserialize(fstream& file)
{
        /* Assumes that file stream read position is already set.
         *
         * Deserialize each polymorphic type by calling its own
         * deseralize method. Each one knows how to correctly load
         * its type's data from file.
         */
    
        short unsigned int type_val;
        PlayerType type;

        // Read the unique id of the game save data
        file.read(uid, sizeof(uid));

        // Seek past (skip) the game size
        file.seekg(sizeof(int), ios::cur);
        
        // Read the current turn
        file.read(reinterpret_cast<char*>(&turn), sizeof(turn));
        
        // Conditionally clear old allocated memory for this->p1 and this->p2
        if (clr) {
            delete this->p1;
            this->p1 = nullptr;
            delete this->p2;
            this->p2 = nullptr;
        } else {
            this->clr = true;  // If not already true, set to true (clear next time)
        }

        //// Deserialize p1 (Player 1)
        
        // Read the Player object type
        file.read(reinterpret_cast<char*>(&type_val), sizeof(type_val));
        type = static_cast<PlayerType>(type_val);
        
        // get new p1; Use appropriate serialization method for type
        switch (type) {
            case PlayerType::PLAYER: {
                Player* p1 = new Player();
                p1->deserialize(file);
                this->p1 = p1;
                break;
            }
            case PlayerType::COMP: {
                Comp* p1 = new Comp();
                p1->deserialize(file);
                this->p1 = p1;
                break;
            }
        }
    
        //// Deserialize p2 (Player 2)

        // Read the Player object type
        file.read(reinterpret_cast<char*>(&type_val), sizeof(type_val));
        type = static_cast<PlayerType>(type_val);
        
        // get new p2; Use appropriate serialization method for type
        switch (type) {
            case PlayerType::PLAYER: {
                Player* p2 = new Player();
                p2->deserialize(file);
                this->p2 = p2;
                break;
            }
            case PlayerType::COMP: {
                Comp* p2 = new Comp();
                p2->deserialize(file);
                this->p2 = p2;
                break;
            }
        }
}
