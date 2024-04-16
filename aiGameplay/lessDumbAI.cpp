/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/*
 * File:   main.cpp
 * Author: hermo
 *
 * Created on April 14, 2024, 4:36 PM
 */

#include <cstdlib>
#include <iostream>
#include <time.h>  /* for time() */
#include <stdlib.h>  /* for rand() and srand() */

using namespace std;

int quadrantDetector(int width, int height, int x, int y) {     // Width and height of gameboard, x & y coordinates of point (j is x and i is y)
    int quadrant = 1;
    if (x >= width/2 && y < height/2) {         // Quadrant 1 (Top right)
        quadrant = 1;
    }
    else if (x < width/2 && y < height/2) {     // Quadrant 2 (Top left)
        quadrant = 2;
    }
    else if (x < width/2 && y >= height/2) {    // Quadrant 3 (Bottom left)
        quadrant = 3;
    }
    else if (x >= width/2 && y >= height/2) {   // Quadrant 4 (Bottom right)
        quadrant = 4;
    }
    return quadrant;
}

bool movesAvailable(char board[10][10], int quadrant) {        // Check if moves are available
    int ti, tj;
    int iLim, jLim;         // Limits for for loops
    if (quadrant == 1) {
        ti = 0;
        tj = 10/2;
        iLim = 10/2;
        jLim = 10;
    }
    else if (quadrant == 2) {
        ti = 0;
        tj = 0;
        iLim = 10/2;
        jLim = 10/2;
    }
    else if (quadrant == 3) {
        ti = 10/2;
        tj = 0;
        iLim = 10;
        jLim = 10/2;
    }
    else {
        ti = 10/2;
        tj = 10/2;
        iLim = 10;
        jLim = 10;
    }

    for (int i = ti; i < iLim; i++) {
        for (int j = tj; j < jLim; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return true;
            }
        }
    }

    return false;
}

bool getRandomPointInQuadrant(char board[10][10], int quadrant, int width, int height, int &x, int &y) {      // Width and height of board, Want to pass the x,y coords through params, bool return true for successful & false for no more points in that quadrant
    srand(time(NULL));
    int i, j;
    if (quadrant == 1) {
        i = 0;
        j = 10/2;
    }
    else if (quadrant == 2) {
        i = 0;
        j = 0;
    }
    else if (quadrant == 3) {
        i = 10/2;
        j = 0;
    }
    else if (quadrant == 4) {
        i = 10/2;
        j = 10/2;
    }
    int tempX, tempY;
    if (movesAvailable(board, quadrant)) {
        char square;

        do {
            tempX = j + rand() % (10/2);    // Reversed x & y because [i][j] has j as x coordinate (horizontal)
            tempY = i + rand() % (10/2);
            square = board[tempY][tempX];
        } while (square == 'X' || square == 'O');   // Keep changing while x or o

        x = tempX;
        y = tempY;

        return true;    // Successful
    }
    else {
        return false;   // No more moves in quadrant
    }
}

class ComputerPlayer {
private:
    int state;      // States: 0 - Linear search
                    //         1 - Narrowed search

    int guesses;    // Will need to be tweaked for number of boats. Not needed for smarter ai
    // Don't know how implementation will work with ending the game yet, could fit in here or have overall game detect it

    // Number of guesses per quadrant are reset upon hitting again
    // Will continue until no more squares left or misses on all guesses. If you get to that point, reset quadrant, change state and linear

    bool smart;     // Difference between less dumb ai and smart ai

    int quadrant;   // ONLY for less dumb ai

    int score;      // Increment as you get hits


    // Can maybe keep next move or initial state in here
public:
    ComputerPlayer() {  // Initializing our computer player by default will be:
        state = 0;
        guesses = 10;       // Tweaking to be 10
        quadrant = 0;
        score = 0;
        smart = false;
    }

    ComputerPlayer(int s, int g, bool smrt) {
        state = s;
        guesses = g;
        quadrant = 0;
        score = 0;
        smart = smrt;
    }

    bool isSmart() {
        if (smart) {
            return true;
        }
        else {
            return false;
        }
    }

    void shoot(char board[10][10]) {      // These sizes will need to be passed in somehow
        bool shot = false;                // Shot flag
        if (!state) {                     // We are in linear search state
            // Given the nature of our gameboard, we don't need to keep track of where we left off on the linear search
            // as we can simply begin where we started and iterate until we get to a point where we haven't guessed
            int i = 0, j = 0;
            for (i = 0; i < 10; i++) {          // For now, we will do a simple linear traversal (Originally planned on a modified linear search where you alternate lines)
                for (j = 0; j < 10; j++) {
                    // board[i][j] == '-' || board[i][j] == 'A' || board[i][j] == 'B' || board[i][j] == 'C' || board[i][j] == 'D' || board[i][j] == 'S'
                    if (board[i][j] != 'X' && board[i][j] != 'O') {     // This makes the algo un biased
                        if (board[i][j] == '-') {       // Was a miss
                            board[i][j] = 'O';
                        }
                        else {
                            // Shot hit
                            // Detect quadrant
                            quadrant = quadrantDetector(10, 10, j, i);
                            // Set to narrowed state
                            state = 1; // (not yet)
                            // Change to hit
                            if (i == 1 && j == 6) {
                                cout << "Get here";
                            }

                            board[i][j] = 'X';
                            score++;
                        }
                        shot = true;
                        break;
                    }
                    else {
                        continue;
                    }
                }
                if (shot) {
                    break;
                }
            }
            if (i == 10 && j == 10) {
                // Reached the end, stop iterating as you've made all guesses
                // Could be a kill switch or something, but as of now, I don't think it'll reach this
                cout << "No more moves left!" << endl;
            }
        }
        else {
            // Going to have to double-check the guesses system
            if (guesses <= 0) {
                guesses = 10;       // Tweak this
            }

            int i, j;
            bool status = getRandomPointInQuadrant(board, quadrant, 10, 10, j, i);
            bool hitFlag = false;
            if (status) {       // Success?
                if (board[i][j] == '-') {
                    board[i][j] = 'O';
                    cout << "\nMissed!\n";
                }
                else {
                    board[i][j] = 'X';
                    score++;
                    hitFlag = true;
                    cout << "\nHit!\n";
                }
            }
            else {
                cout << "No more moves in quadrant!";
                // Nothing happens for now, but it should get a retry no?
                // Set it to state 0 and count this as a hit?
                hitFlag = true;
                state = 0;
                // Recursively calls itself
                this->shoot(board);
            }

            if (hitFlag) {
                guesses++;
                state = 1;
            }
            else {
                guesses--;
                if (guesses <= 0) {
                    state = 0;
                }
            }
        }
    }

    bool isGameOver() {
        if (score == 17) {
            return true;
        }
        else {
            return false;
        }
    }
};

void printBoard(char board[10][10]) {
    cout << "\n";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << board[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

int main(int argc, char** argv) {
    // Algorithm:
    // Perform a linear search across the 2D array
    // Upon a hit, detect what quadrant the hit was detected in
    // Make N/4 guesses within that quadrant until no more hits or spots available (N = sum or spaces occupied by ships)

    // Using a 2D character array where:

    /*
     * '-' == Empty Cell
     * 'X' == Hit Cell
     * 'O' == Miss Cell
     * 'A' == Aircraft Carrier Cell (5 squares)
     * 'B' == Battleship (4 squares)
     * 'D' == Destroyer (3 squares)
     * 'S' == Submarine (3 squares)
     * 'C' == Cruiser (2 squares)
     */

    // Create gameboard instance (In process of creating computer generated ship placement
    char gameBoard[10][10] = {
        {'-','A','-','-','-','-','-','-','-','-'},
        {'-','A','-','-','-','-','B','B','B','B'},
        {'-','A','-','-','D','-','-','-','-','-'},
        {'-','A','-','-','D','-','-','-','-','-'},
        {'-','A','-','-','D','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','S','S','S','-'},
        {'-','-','C','C','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-'}
    };

    // This algorithm has two states
    // Linear hunt
    // Scoped hunt in quadrant n
    // Need to maintain this state over the iterations of turns


    // Function needs to be called multiple times and know what state its in
    ComputerPlayer *Leo = new ComputerPlayer();
    if (!Leo->isSmart()) {
        cout << "Leo is not smart\n";
    }

    int i;
    for (i = 0; i < 100; i++) {
        Leo->shoot(gameBoard);
        printBoard(gameBoard);
        if (Leo->isGameOver()) {
            break;
        }
    }

    cout << "\nGame ended at round " << i;

    return 0;
}

