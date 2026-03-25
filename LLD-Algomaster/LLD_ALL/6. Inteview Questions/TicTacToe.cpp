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
    PlayingPiece(PieceType t) : type(t) {}
};

/* ---------- PLAYER ---------- */
class Player {
public:
    string name;
    PlayingPiece piece;

    Player(string n, PieceType t) : name(n), piece(t) {}
};

/* ---------- BOARD ---------- */
class Board {
public:
    int size;
    vector<vector<PlayingPiece*>> grid;

    Board(int n) : size(n) {
        grid.resize(size, vector<PlayingPiece*>(size, nullptr));
    }

    bool addPiece(int row, int col, PlayingPiece* piece) {
        if (row < 0 || col < 0 || row >= size || col >= size)
            return false;
        if (grid[row][col] != nullptr)
            return false;

        grid[row][col] = piece;
        return true;
    }

    void printBoard() {
        cout << "\n";
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
        return true;
    }
};

/* ---------- GAME ---------- */
class TicTacToeGame {
public:
    Board board;
    deque<Player*> players;
    Player* winner = nullptr;

    TicTacToeGame() : board(3) {}

    void initializeGame() {
        Player* p1 = new Player("Player1", PieceType::X);
        Player* p2 = new Player("Player2", PieceType::O);

        players.push_back(p1);
        players.push_back(p2);
    }

    GameStatus startGame() {
        while (true) {
            Player* currPlayer = players.front();
            players.pop_front();

            board.printBoard();
            cout << currPlayer->name << " (" 
                 << (currPlayer->piece.type == PieceType::X ? "X" : "O")
                 << ") enter row and col: ";

            int row, col;
            cin >> row >> col;

            bool success = board.addPiece(row, col, &currPlayer->piece);
            if (!success) {
                cout << "Invalid move! Try again.\n";
                players.push_front(currPlayer);
                continue;
            }

            if (checkWinner(row, col, currPlayer->piece.type)) {
                board.printBoard();
                winner = currPlayer;
                return GameStatus::WIN;
            }

            if (board.isFull()) {
                board.printBoard();
                return GameStatus::DRAW;
            }

            players.push_back(currPlayer);
        }
    }

    bool checkWinner(int row, int col, PieceType type) {
        bool win;

        // Row check
        win = true;
        for (int j = 0; j < board.size; j++)
            if (board.grid[row][j] == nullptr || board.grid[row][j]->type != type)
                win = false;
        if (win) return true;

        // Column check
        win = true;
        for (int i = 0; i < board.size; i++)
            if (board.grid[i][col] == nullptr || board.grid[i][col]->type != type)
                win = false;
        if (win) return true;

        // Diagonal
        if (row == col) {
            win = true;
            for (int i = 0; i < board.size; i++)
                if (board.grid[i][i] == nullptr || board.grid[i][i]->type != type)
                    win = false;
            if (win) return true;
        }

        // Anti-diagonal
        if (row + col == board.size - 1) {
            win = true;
            for (int i = 0; i < board.size; i++)
                if (board.grid[i][board.size - i - 1] == nullptr ||
                    board.grid[i][board.size - i - 1]->type != type)
                    win = false;
            if (win) return true;
        }

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
