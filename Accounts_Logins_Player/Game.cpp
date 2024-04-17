/* 
 * File:   Game.cpp
 * Author: hanne
 * 
 * Created on April 14, 2024, 1:44 PM
 */

#include "Game.h"

Game::Game() {
    p1 = new Player();
    p2 = new Player();
    this->turn = false;
}

Game::Game(Player* p1, Player* p2) {
    this->p1 = p1;
    this->p2 = p2;
    this->turn = false;
}


/// @brief Update whose turn it is
void Game::doTurn() {
    turn = !turn;
}
void Game::play(){
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

    while(p2->getUnsunk() > 0 || p1->getUnsunk() > 0){
        
        cout << "Commence attack. Enter row and col coordinates:" << endl;
        cin >> letter >> row;
        col = letter - 65;
        p1->attackCell(row, col, p2);
        p1->displayShots();
    }
}
