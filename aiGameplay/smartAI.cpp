#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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

public:
    void shoot(char board[10][10]);
    void hitSmart(char board[10][10]);
    void linsearch(char board[10][10]);
    void clearLastHit();
    void setLastHit(int x, int y);
    bool checkHit(char board[10][10], int x, int y);
    bool sunk(char board[10][10]);
    void printBoard(char board[10][10]);
};

void ComputerPlayer::linsearch(char board[10][10]) {
    bool searchEven = rand() % 2 == 0;  // Random even or odd row search
    if (searchEven != lastSearchEven) {
        cout << "Switching search pattern from " << (lastSearchEven ? "even" : "odd") << " to " << (searchEven ? "even" : "odd") << " rows." << endl;
        printBoard(board);
        lastSearchEven = searchEven;
    }
    vector<int> column(10);
    for (int i = 0; i < 10; i++) {
        column[i] = i;
    }
    random_shuffle(column.begin(), column.end());

    int startRow = searchEven ? 1 : 0; 
    cout << "Searching " << (searchEven ? "even rows (2, 4, 6, 8, 10)" : "odd rows (1, 3, 5, 7, 9)") << endl;

    for (int i = startRow; i < 10; i += 2) {
        for (int j : column) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                if (checkHit(board, j, i)) {
                    setLastHit(j, i);
                    return;
                }
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
    if (x < 0 || x >= 10 || y < 0 || y >= 10) return false;  // Boundary check
    if (board[y][x] == 'X' || board[y][x] == 'O') return false;

    if (board[y][x] != '-') {
        board[y][x] = 'X';
        cout << "Hit at [" << y + 1 << ", " << x + 1 << "]" << endl;
        hitHistory.push_back({x, y});  // Save successful hit
        return true;
    } else {
        board[y][x] = 'O';
        cout << "Miss at [" << y + 1 << ", " << x + 1 << "]" << endl;
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
    cout << "all ships are sunk:" << endl;
    cp.printBoard(gameBoard);

    return 0;
}
