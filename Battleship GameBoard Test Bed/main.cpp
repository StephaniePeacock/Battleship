#include <iostream>
#include <unordered_map>

using namespace std;

const int BOARD_SIZE = 10;
const char EMPTY_CELL = '-';
const char SHIP_CELL = 'S';
const char HIT_CELL = 'X';
const char MISS_CELL = 'O';

class GameBoard {
private:
    char board[BOARD_SIZE][BOARD_SIZE];
    unordered_map<char, int> shipCounts;

public:
    // Constructor to initialize the board with empty cells
    GameBoard() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board[i][j] = EMPTY_CELL;
            }
        }
        shipCounts['C'] = 1; // Carrier
        shipCounts['B'] = 2; // Battleship
        shipCounts['D'] = 3; // Destroyer
        shipCounts['S'] = 3; // Submarine
        shipCounts['P'] = 4; // Patrol Boat
    }

    // Function to display the current state of the board
    void displayBoard() {
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

    // Function to check if a given coordinate is within the bounds of the board
    bool isValidCoordinate(int row, int col) {
        return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
    }

    // Function to check if a ship can be placed at the given coordinate
    bool isValidPlacement(int row, int col, int size, char direction) {
        if (!isValidCoordinate(row, col) || (direction != 'H' && direction != 'V'))
            return false;

        if (direction == 'H') {
            if (col + size - 1 >= BOARD_SIZE)
                return false;
            for (int j = col; j < col + size; ++j) {
                if (board[row][j] == SHIP_CELL)
                    return false;
            }
        }
        else { // direction == 'V'
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
    bool placeShip(int row, int col, int size, char direction, char shipType) {
        if (shipCounts[shipType] <= 0 || !isValidPlacement(row, col, size, direction)) {
            cout << "Invalid placement!" << endl;
            return false;
        }

        if (direction == 'H') {
            for (int j = col; j < col + size; ++j) {
                board[row][j] = SHIP_CELL;
            }
        }
        else { // direction == 'V'
            for (int i = row; i < row + size; ++i) {
                board[i][col] = SHIP_CELL;
            }
        }

        shipCounts[shipType]--;
        displayBoard(); // Display the board after each placement
        return true;
    }

    // Function to prompt the user to place ships on the board
    void promptShipPlacement() {
        char shipTypes[] = { 'C', 'B', 'D', 'S', 'P' };
        for (char shipType : shipTypes) {
            int size = shipType == 'C' ? 5 : shipType == 'B' ? 4 : shipType == 'D' ? 3 : shipType == 'S' ? 3 : 2;
            cout << "Placing " << size << "-unit " << shipType << " ship." << endl;
            while (true) {
                int row, col;
                char direction;
                cout << "Enter starting coordinates (row col) and direction (H for horizontal, V for vertical): ";
                cin >> row >> col >> direction;
                if (placeShip(row, col, size, direction, shipType)) {
                    cout << "Ship placed successfully!" << endl;
                    break;
                }
                else {
                    cout << "Invalid coordinates or ship placement. Try again." << endl;
                }
            }
        }
    }

    // Function to check if a cell has already been hit
    bool isCellAlreadyHit(int row, int col) {
        return (board[row][col] == HIT_CELL || board[row][col] == MISS_CELL);
    }

    // Function to attack a cell on the opponent's board
    void attackCell(int row, int col) {
        if (board[row][col] == SHIP_CELL) {
            cout << "Hit!" << endl;
            board[row][col] = HIT_CELL;
        }
        else {
            cout << "Miss!" << endl;
            board[row][col] = MISS_CELL;
        }
    }
};

int main() {
    // Create two game boards, one for each player
    GameBoard player1Board;
    GameBoard player2Board;
    char row;
    char col;

    // Prompt player 1 to place ships on the board
    cout << "Player 1, please place your ships:" << endl;
    player1Board.promptShipPlacement();

    // Display player 1's board after ship placement
    cout << "Player 1's Board after ship placement:" << endl;
    player1Board.displayBoard();

    cout << "Commence attack. Enter row and col coordinates:" << endl;
    cin >> row >> col;
    player1Board.attackCell(row, col);
    return 0;
}
