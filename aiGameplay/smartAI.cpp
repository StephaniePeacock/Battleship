#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <random>

using namespace std;

struct Point {
    int x, y;
};

class ComputerPlayer {
private:
    Point lastHit;
    bool hasLastHit = false;
    vector<Point> hitHistory;  // Track history of hits
    bool lastSearchEven = false;  // check when the row search changes even or odd
    int consecutiveMisses = 0;  // Track consecutive misses
    int moves = 0; // number of moves

public:
    void shoot(char board[10][10]);
    void hitSmart(char board[10][10]);
    void linsearch(char board[10][10]);
    void clearLastHit();
    void setLastHit(int x, int y);
    bool checkHit(char board[10][10], int x, int y);
    bool sunk(char board[10][10]);
    void printBoard(char board[10][10]);
    int getMoves() const { return moves; }
};

void ComputerPlayer::linsearch(char board[10][10]) {
    random_device rd; 
    mt19937 gen(rd()); 
    uniform_int_distribution<> distColumn(0, 9);

    vector<int> rows = lastSearchEven ? vector<int>{1, 3, 5, 7, 9} : vector<int>{0, 2, 4, 6, 8};
    uniform_int_distribution<> distRow(0, rows.size() - 1);
    printBoard(board);
    cout << "Searching " << (lastSearchEven ? "even rows (2, 4, 6, 8, 10)" : "odd rows (1, 3, 5, 7, 9)") << endl;

    bool keepSearching = true;
    while (keepSearching) {
        int rowIndex = rows[distRow(gen)]; 
        int columnIndex = distColumn(gen);

        if (board[rowIndex][columnIndex] != 'X' && board[rowIndex][columnIndex] != 'O') {
            if (checkHit(board, columnIndex, rowIndex)) {
                setLastHit(columnIndex, rowIndex);
                keepSearching = false; 
            }
            if (consecutiveMisses >= 3) {
                lastSearchEven = !lastSearchEven;
                cout << "Switching search pattern due to 3 consecutive misses. Now searching " << (lastSearchEven ? "even rows" : "odd rows") << "." << endl;
                printBoard(board);
                consecutiveMisses = 0;
                keepSearching = false;
            }
        }
    }
}

void ComputerPlayer::hitSmart(char board[10][10]) {
    if (!hasLastHit) return;

    int directions[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};  // Right, Up, Left, Down
    for (int d = 0; d < 4; ++d) {
        int x = directions[d][0], y = directions[d][1];
        int nx = lastHit.x + x, ny = lastHit.y + y;
        while (nx >= 0 && nx < 10 && ny >= 0 && ny < 10) {
            if (!checkHit(board, nx, ny)) break;
            nx += x;
            ny += y;
        }
    }

    clearLastHit();  // Reset the last hit after completion
    linsearch(board);  // Return to random shooting
}

void ComputerPlayer::shoot(char board[10][10]) {
    while (!sunk(board)) {
        if (hasLastHit) {
            hitSmart(board);
        } else {
            linsearch(board);
        }
    }
}

bool ComputerPlayer::checkHit(char board[10][10], int x, int y) {
    moves++;
    if (x < 0 || x >= 10 || y < 0 || y >= 10) return false;
    if (board[y][x] == 'X' || board[y][x] == 'O') return false;

    if (board[y][x] != '-') {
        board[y][x] = 'X';
        cout << "Hit at [" << y + 1 << ", " << x + 1 << "], resetting miss counter." << endl;
        hitHistory.push_back({x, y});
        consecutiveMisses = 0;
        return true;
    } else {
        board[y][x] = 'O';
        consecutiveMisses++;
        cout << "Miss at [" << y + 1 << ", " << x + 1 << "], consecutive misses: " << consecutiveMisses << "." << endl;
        return false;
    }
}


bool ComputerPlayer::sunk(char board[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            char c = board[i][j];
            if (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'S') {
                return false;
            }
        }
    }
    return true;
}

void ComputerPlayer::clearLastHit() {
    hasLastHit = false;
    hitHistory.clear();
}

void ComputerPlayer::setLastHit(int x, int y) {
    lastHit.x = x;
    lastHit.y = y;
    hasLastHit = true;
}

void ComputerPlayer::printBoard(char board[10][10]) {
    cout << "\n";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    srand(time(NULL));  // Seed the random number generator once(it will "randomize" the same spot if it's on a function)
    char gameBoard[10][10] = {
        {'-', 'A', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', 'A', '-', '-', '-', '-', 'B', 'B', 'B', 'B'},
        {'-', 'A', '-', '-', 'D', '-', '-', '-', '-', '-'},
        {'-', 'A', '-', '-', 'D', '-', '-', '-', '-', '-'},
        {'-', 'A', '-', '-', 'D', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', 'S', 'S', 'S', '-'},
        {'-', '-', 'C', 'C', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'}
    };

    ComputerPlayer cp;
    cp.shoot(gameBoard);
    cout << "All ships are sunk after " << cp.getMoves() << " moves." << endl;
    cp.printBoard(gameBoard);

    return 0;
}
