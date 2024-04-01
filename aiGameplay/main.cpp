#include <cstdlib>
#include <iostream>
#include <time.h>  /* for time() */
#include <stdlib.h>  /* for rand() and srand() */
using namespace std;

// Just a quick "all in one" implementation of a dumb AI that chooses random spaces on a 2D array grid
// Could change to 1D array or 2D array later on, but just wanted to get a basic implementation down first

// Dumb AI implementation notes: 
// - Will not choose a repeat shot
//      - Will recursively call itself to get a valid shot that is either a hit or miss and not a repeat shot


// Going to separate into header files soon

// Read the comments to follow along


bool movesAvailable(int grid[10][10]) {     // Checks if moves are available
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j] != 2) {
                return true;
            }
        }
    }
    return false;
}

int dumbMove(int grid[10][10], int &sX, int &sY) {        // If return is 0 - miss, 1 - hit, 2 - repeated shot
    int x = rand() % 10;
    int y = rand() % 10;

    int space = grid[x][y];

    if (space == 0) {                   // If space is 0
        grid[x][y] = 2;                 // Change shot history
        sX = x;                         // Save shot coordinates
        sY = y;
        return 0;                       // Then your shot missed
    }
    else if (space == 1) {              // If space is 1
        grid[x][y] = 2;                 // Change shot history
        sX = x;                         // Save shot coordinates
        sY = y;
        return 1;                       // Then your shot hit
    }
    else {                              // Else, this space was shot at before
        if (movesAvailable(grid)) {     // Moves available
            return dumbMove(grid, sX, sY);      // Try again
        }
        else {
            return 2;                   // No moves available, just return
        }
    }
}



int main(int argc, char** argv) {
    srand(time(NULL));

    // Create a 10x10 grid from a 2D array
    const int LENGTH = 10;
    const int WIDTH = 10;

    // Grid initialization
    int grid[LENGTH][WIDTH];

    // Initialize array with zeros first
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = 0;
        }
    }

    // Randomly set up 1x1 boats at spaces in grid
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int r = rand() % 3;             // Value of either: 0, 1, 2
            grid[i][j] = r;                 // 0: no boat, 1: boat, 2: Already been shot
        }
    }

    // Preview of grid
    cout << endl;
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }

    // Make one dumb move
    cout << endl << "Shooting..." << endl;
    // Save coordinates
    int x = -1,         // If still -1 after, then no valid moves, regardless this isn't the check (The return from dumbMove() is).
        y = -1;         // Just don't want to leave it defined (Which it can be)
    int shot = dumbMove(grid, x, y);
    if (shot == 0) {
        cout << "Miss on coordinate: (" << x << ", " << y << ")" << endl;
    }
    else if (shot == 1) {
        cout << "Hit on coordinate: (" << x << ", " << y << ")" << endl;
    }
    else {
        cout << "No more moves!" << endl;
    }

    // Grid after one dumb move:
    cout << endl;
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }

    // Let's test different cases:
    // - What if there are no more available spaces to shoot at? Ex: All spaces are 2's (Every space has been shot at)
    // - What if there are only 2 available spaces to shoot at? Ex: All but two spaces are 2's (You have shot at every space but two)
    // - What if there is only 1 available space to shoot at? Ex: All but one space are 2's (You have shot at every space but one)

    // Test case 1:
    cout << endl << "Test case 1: All spaces are 2's (Every space has been shot at)" << endl;
    // Initialize grid to all 2's
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = 2;
        }
    }
    // Make one dumb move on test case 1
    cout << endl << "Shooting..." << endl;
    int x1, y1;
    int shot1 = dumbMove(grid, x1, y1);
    if (shot1 == 0) {
        cout << "Miss on coordinate: (" << x1 << ", " << y1 << ")" << endl;
    }
    else if (shot1 == 1) {
        cout << "Hit on coordinate: (" << x1 << ", " << y1 << ")" << endl;
    }
    else {
        cout << "No more moves!" << endl;
    }


    // Test case 2:
    cout << endl << "Test case 2: All but two spaces are 2's (You have shot at every space but two)" << endl;
    // Initialize grid to all 2's
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = 2;
        }
    }
    // Set two spaces that have yet to be shot at
    grid[9][8] = 0;
    grid[9][9] = 1;
    // Make one dumb move on test case 2 (Run multiple times to see that it alternates between missing and hitting a boat)
    cout << endl << "Shooting..." << endl;
    int x2, y2;
    int shot2 = dumbMove(grid, x2, y2);
    if (shot2 == 0) {
        cout << "Miss on coordinate: (" << x2 << ", " << y2 << ")" << endl;
    }
    else if (shot2 == 1) {
        cout << "Hit on coordinate: (" << x2 << ", " << y2 << ")" << endl;
    }
    else {
        cout << "No more moves!" << endl;
    }

    // Test case 3:
    cout << endl << "Test case 3: All but one space are 2's (You have shot at every space but one)" << endl;
    // Initialize grid to all 2's
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = 2;
        }
    }
    // Set one space that has yet to be shot at
    grid[9][9] = 1;        // Only space left is a hit
    // Make one dumb move on test case 3 (Should always hit)
    cout << endl << "Shooting..." << endl;
    int x3, y3;
    int shot3 = dumbMove(grid, x3, y3);
    if (shot3 == 0) {
        cout << "Miss on coordinate: (" << x3 << ", " << y3 << ")" << endl;
    }
    else if (shot3 == 1) {
        cout << "Hit on coordinate: (" << x3 << ", " << y3 << ")" << endl;
    }
    else {
        cout << "No more moves!" << endl;
    }

    return 0;
}



