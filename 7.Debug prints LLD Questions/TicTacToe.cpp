#include <bits/stdc++.h>
using namespace std;

/* ---------- ENUMS ---------- */
enum class GameStatus {
    WIN,
    DRAW,
    IN_PROGRESS
};

enum class PieceType {
    X,
    O,
    EMPTY
};

/* ---------- PLAYING PIECE ---------- */
class PlayingPiece {
public:
    PieceType type;
    PlayingPiece(PieceType t) : type(t) {
        cout << "[DEBUG] PlayingPiece created: "
             << (t == PieceType::X ? "X" : "O") << endl;
    }
};

/* ---------- PLAYER ---------- */
class Player {
public:
    string name;
    PlayingPiece piece;

    Player(string n, PieceType t) : name(n), piece(t) {
        cout << "[DEBUG] Player created: " << name
             << " with piece "
             << (t == PieceType::X ? "X" : "O") << endl;
    }
};

/* ---------- BOARD ---------- */
class Board {
public:
    int size;
    vector<vector<PlayingPiece*>> grid;

    Board(int n) : size(n) {
        grid.resize(size, vector<PlayingPiece*>(size, nullptr));
        cout << "[DEBUG] Board initialized with size " << size << "x" << size << endl;
    }

    bool addPiece(int row, int col, PlayingPiece* piece) {
        cout << "[DEBUG] Attempting to add piece at (" << row << ", " << col << ")\n";

        if (row < 0 || col < 0 || row >= size || col >= size) {
            cout << "[DEBUG] Move out of bounds\n";
            return false;
        }

        if (grid[row][col] != nullptr) {
            cout << "[DEBUG] Cell already occupied\n";
            return false;
        }

        grid[row][col] = piece;
        cout << "[DEBUG] Piece placed successfully\n";
        return true;
    }

    void printBoard() {
        cout << "\n[DEBUG] Current Board State:\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (grid[i][j] == nullptr)
                    cout << " _ ";
                else if (grid[i][j]->type == PieceType::X)
                    cout << " X ";
                else
                    cout << " O ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool isFull() {
        for (auto &row : grid)
            for (auto &cell : row)
                if (cell == nullptr)
                    return false;

        cout << "[DEBUG] Board is full\n";
        return true;
    }
};

/* ---------- GAME ---------- */
class TicTacToeGame {
public:
    Board board;
    deque<Player*> players;
    Player* winner = nullptr;
    int turn = 1;

    TicTacToeGame() : board(3) {}

    void initializeGame() {
        cout << "[DEBUG] Initializing game\n";

        Player* p1 = new Player("Player1", PieceType::X);
        Player* p2 = new Player("Player2", PieceType::O);

        players.push_back(p1);
        players.push_back(p2);

        cout << "[DEBUG] Players added to queue\n";
    }

    GameStatus startGame() {
        cout << "[DEBUG] Game started\n";

        while (true) {
            Player* currPlayer = players.front();
            players.pop_front();

            cout << "---------------------------------\n";
            cout << "[TURN " << turn++ << "] "
                 << currPlayer->name << "'s move\n";

            board.printBoard();

            cout << currPlayer->name << " ("
                 << (currPlayer->piece.type == PieceType::X ? "X" : "O")
                 << ") enter row and col: ";

            int row, col;
            cin >> row >> col;

            cout << "[DEBUG] Input received: row=" << row
                 << ", col=" << col << endl;

            bool success = board.addPiece(row, col, &currPlayer->piece);
            if (!success) {
                cout << "[DEBUG] Invalid move. Retrying same player\n";
                players.push_front(currPlayer);
                continue;
            }

            if (checkWinner(row, col, currPlayer->piece.type)) {
                cout << "[DEBUG] Winner detected\n";
                board.printBoard();
                winner = currPlayer;
                return GameStatus::WIN;
            }

            if (board.isFull()) {
                cout << "[DEBUG] Draw detected\n";
                board.printBoard();
                return GameStatus::DRAW;
            }

            players.push_back(currPlayer);
        }
    }

    bool checkWinner(int row, int col, PieceType type) {
        bool win;

        cout << "[DEBUG] Checking winner for "
             << (type == PieceType::X ? "X" : "O") << endl;

        // Row
        win = true;
        for (int j = 0; j < board.size; j++)
            if (board.grid[row][j] == nullptr ||
                board.grid[row][j]->type != type)
                win = false;
        if (win) {
            cout << "[DEBUG] Row win detected\n";
            return true;
        }

        // Column
        win = true;
        for (int i = 0; i < board.size; i++)
            if (board.grid[i][col] == nullptr ||
                board.grid[i][col]->type != type)
                win = false;
        if (win) {
            cout << "[DEBUG] Column win detected\n";
            return true;
        }

        // Diagonal
        if (row == col) {
            win = true;
            for (int i = 0; i < board.size; i++)
                if (board.grid[i][i] == nullptr ||
                    board.grid[i][i]->type != type)
                    win = false;
            if (win) {
                cout << "[DEBUG] Diagonal win detected\n";
                return true;
            }
        }

        // Anti-diagonal
        if (row + col == board.size - 1) {
            win = true;
            for (int i = 0; i < board.size; i++)
                if (board.grid[i][board.size - i - 1] == nullptr ||
                    board.grid[i][board.size - i - 1]->type != type)
                    win = false;
            if (win) {
                cout << "[DEBUG] Anti-diagonal win detected\n";
                return true;
            }
        }

        cout << "[DEBUG] No win found\n";
        return false;
    }
};

/* ---------- MAIN ---------- */
int main() {
    cout << "\n===>>> TicTacToe Game\n";

    TicTacToeGame game;
    game.initializeGame();
    GameStatus status = game.startGame();

    cout << "\n===>>> GAME OVER: ";
    if (status == GameStatus::WIN)
        cout << game.winner->name << " won the game\n";
    else if (status == GameStatus::DRAW)
        cout << "It's a Draw!\n";
    else
        cout << "Game Ended\n";

    return 0;
}
