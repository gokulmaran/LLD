#include <iostream>
using namespace std;

//https://github.com/ashishps1/awesome-low-level-design/blob/main/solutions/cpp/vendingmachine/README.md
/*Features
The Tic-Tac-Toe game should be played on a 3x3 grid.
Two players take turns marking their symbols (X or O) on the grid.
The first player to get three of their symbols in a row (horizontally, vertically, or diagonally) wins the game.
If all the cells on the grid are filled and no player has won, the game ends in a draw.
The game should have a user interface to display the grid and allow players to make their moves.
The game should handle player turns and validate moves to ensure they are legal.
The game should detect and announce the winner or a draw at the end of the game.

Entities
The Player class represents a player in the game, with a name and a symbol (X or O).
The Board class represents the game board, which is a 3x3 grid. It provides methods to make moves, check for a winner, and check if the board is full.
The Game class manages the game flow and player interactions. It handles player turns, validates moves, and determines the winner or a draw.
The TicTacToe class(main) is the entry point of the application and creates instances of the players and the game.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ================== Symbol Enum ==================
// FIX 1: Added semicolon after enum
// FIX 2: Use enum class for better type safety
enum class Symbol {
    X,
    O,
    EMPTY
};

// Helper function to convert Symbol -> char
// FIX 3: You were mixing char and Symbol everywhere
char symbolToChar(Symbol s) {
    if (s == Symbol::X) return 'X';
    if (s == Symbol::O) return 'O';
    return ' ';
}

// ================== Player ==================
class Player {
public:
    string name;
    Symbol symbol;

    Player(string name, Symbol playerSymbol)
        : name(name), symbol(playerSymbol) {}
};

// ================== Board ==================
class Board {
public:
    static const int size = 3;

private:
    vector<vector<Symbol>> grid;  // FIX 4: Changed char grid -> Symbol grid

public:
    Board() {
        // FIX 5: Your vector initialization syntax was wrong
        grid = vector<vector<Symbol>>(size, vector<Symbol>(size, Symbol::EMPTY));
    }

    bool makeMove(int r, int c, Symbol symbol) {
        // FIX 6: Used size instead of hardcoded 3
        if (r < 0 || r >= size || c < 0 || c >= size) {
            return false;
        }

        if (grid[r][c] != Symbol::EMPTY) {
            return false;
        }

        grid[r][c] = symbol;
        return true;
    }

    bool isFull() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (grid[i][j] == Symbol::EMPTY) {
                    return false;
                }
            }
        }
        return true;
    }

    Symbol checkWinner() {

        // Rows
        for (int i = 0; i < size; i++) {
            if (grid[i][0] != Symbol::EMPTY &&
                grid[i][0] == grid[i][1] &&
                grid[i][1] == grid[i][2]) {
                return grid[i][0];
            }
        }

        // Columns
        for (int i = 0; i < size; i++) {
            if (grid[0][i] != Symbol::EMPTY &&
                grid[0][i] == grid[1][i] &&
                grid[1][i] == grid[2][i]) {
                return grid[0][i];
            }
        }

        // Diagonals
        // FIX 7: Your diagonal condition was wrong + unsafe
        if (grid[0][0] != Symbol::EMPTY &&
            grid[0][0] == grid[1][1] &&
            grid[1][1] == grid[2][2]) {
            return grid[0][0];
        }

        if (grid[0][2] != Symbol::EMPTY &&
            grid[0][2] == grid[1][1] &&
            grid[1][1] == grid[2][0]) {
            return grid[0][2];
        }

        return Symbol::EMPTY;
    }

    void printBoard() {
        // FIX 8: Your print loop was outside function + incorrect formatting
        cout << "\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << symbolToChar(grid[i][j]);
                if (j < size - 1)
                    cout << " | ";
            }
            cout << "\n";
            if (i < size - 1)
                cout << "--+---+--\n";
        }
        cout << "\n";
    }
};

// ================== Game ==================
class Game {
private:
    Board board;
    Player player1;
    Player player2;
    Player* currentPlayer;

    void switchPlayer() {
        // FIX 9: Your ternary operator did nothing (no assignment)
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }

public:
    // FIX 10: You used player1/player2 but never declared them in class
    Game(Player p1, Player p2)
        : player1(p1), player2(p2), currentPlayer(&player1) {}

    void start() {
        cout << "Game Started\n";

        while (true) {
            board.printBoard();

            cout << currentPlayer->name
                 << " (" << symbolToChar(currentPlayer->symbol)
                 << ") enter row and column: ";

            int row, col;
            cin >> row >> col;

            if (!board.makeMove(row, col, currentPlayer->symbol)) {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            Symbol winner = board.checkWinner();

            if (winner != Symbol::EMPTY) {
                board.printBoard();
                cout << currentPlayer->name << " wins the match!\n";
                break;
            }

            if (board.isFull()) {
                board.printBoard();
                cout << "Game is Draw\n";
                break;
            }

            switchPlayer();
        }
    }
};

// ================== Main ==================
int main() {

    // FIX 11: You passed "X" (string) instead of Symbol::X
    Player p1("Player 1", Symbol::X);
    Player p2("Player 2", Symbol::O);

    Game game(p1, p2);
    game.start();

    return 0;
}