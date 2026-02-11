#include <iostream>
#include <vector>
using namespace std;

// ================= ENUM =================
enum class GameStatus {
    IN_PROGRESS,
    DRAW,
    WIN
};

// ================= PLAYER =================
class Player {
public:
    int id;
    char symbol;

    Player(int id, char symbol) : id(id), symbol(symbol) {}
};

// ================= BOARD =================
class Board {
    int rows, cols;
    vector<vector<char>> grid;

public:
    Board(int r = 6, int c = 7) : rows(r), cols(c) {
        grid.assign(rows, vector<char>(cols, '.'));
        cout << "[DEBUG] Board initialized: " << rows << "x" << cols << endl;
    }

    bool isColumnFull(int col) {
        bool full = grid[0][col] != '.';
        cout << "[DEBUG] Checking if column " << col << " is full: "
             << (full ? "YES" : "NO") << endl;
        return full;
    }

    int dropDisc(int col, char symbol) {
        cout << "[DEBUG] Dropping disc '" << symbol << "' in column " << col << endl;
        for (int r = rows - 1; r >= 0; r--) {
            if (grid[r][col] == '.') {
                grid[r][col] = symbol;
                cout << "[DEBUG] Disc placed at row " << r << ", col " << col << endl;
                return r;
            }
        }
        return -1;
    }

    bool isFull() {
        for (int c = 0; c < cols; c++) {
            if (grid[0][c] == '.') return false;
        }
        cout << "[DEBUG] Board is completely full" << endl;
        return true;
    }

    bool checkWin(int row, int col, char symbol) {
        cout << "[DEBUG] Checking win for '" << symbol
             << "' from position (" << row << "," << col << ")" << endl;

        bool win =
            checkDirection(row, col, symbol, 0, 1) ||   // Horizontal
            checkDirection(row, col, symbol, 1, 0) ||   // Vertical
            checkDirection(row, col, symbol, 1, 1) ||   // Diagonal 
            checkDirection(row, col, symbol, 1, -1);    // Diagonal /

        cout << "[DEBUG] Win result: " << (win ? "YES" : "NO") << endl;
        return win;
    }

    void print() {
        cout << "\n";
        for (auto &r : grid) {
            for (char c : r) cout << c << " ";
            cout << "\n";
        }
        cout << "0 1 2 3 4 5 6\n\n";
    }

private:
    bool checkDirection(int row, int col, char symbol, int dr, int dc) {
        int count = 1;
        count += countCells(row, col, symbol, dr, dc);
        count += countCells(row, col, symbol, -dr, -dc);

        cout << "[DEBUG] Direction (" << dr << "," << dc
             << ") count = " << count << endl;

        return count >= 4;
    }

    int countCells(int row, int col, char symbol, int dr, int dc) {
        int r = row + dr, c = col + dc, cnt = 0;
        while (r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == symbol) {
            cnt++;
            r += dr;
            c += dc;
        }
        return cnt;
    }
};

// ================= GAME =================
class Game {
    Board board;
    vector<Player> players;
    int currentPlayer;
    GameStatus status;

public:
    Game() : currentPlayer(0), status(GameStatus::IN_PROGRESS) {
        players.emplace_back(1, 'X');
        players.emplace_back(2, 'O');
        cout << "[DEBUG] Game initialized with 2 players\n";
    }

    void play() {
        while (status == GameStatus::IN_PROGRESS) {
            board.print();
            Player &p = players[currentPlayer];

            cout << "[DEBUG] Current Player Index: " << currentPlayer << endl;

            int col;
            cout << "Player " << p.id << " (" << p.symbol << ") enter column: ";
            cin >> col;

            cout << "[DEBUG] Player " << p.id << " selected column " << col << endl;

            if (col < 0 || col >= 7 || board.isColumnFull(col)) {
                cout << "[DEBUG] Invalid move detected\n";
                cout << "Invalid move. Try again.\n";
                continue;
            }

            int row = board.dropDisc(col, p.symbol);

            if (board.checkWin(row, col, p.symbol)) {
                board.print();
                cout << "Player " << p.id << " wins!\n";
                status = GameStatus::WIN;
                cout << "[DEBUG] Game Status changed to WIN\n";
                return;
            }

            if (board.isFull()) {
                board.print();
                cout << "Game Draw!\n";
                status = GameStatus::DRAW;
                cout << "[DEBUG] Game Status changed to DRAW\n";
                return;
            }

            currentPlayer = (currentPlayer + 1) % 2;
            cout << "[DEBUG] Switching to next player\n";
        }
    }
};

// ================= MAIN =================
int main() {
    cout << "[DEBUG] Starting Connect Four Game\n";
    Game game;
    game.play();
    cout << "[DEBUG] Game Ended\n";
    return 0;
}
