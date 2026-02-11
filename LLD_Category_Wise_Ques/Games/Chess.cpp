#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// ================= ENUMS =================
enum class Color { WHITE, BLACK };
enum class GameStatus { ACTIVE, CHECKMATE, DRAW };

// ================= POSITION =================
struct Position {
    int row, col;
};

// ================= PIECE =================
class Piece {
protected:
    Color color;

public:
    Piece(Color c) : color(c) {}
    virtual ~Piece() {}

    Color getColor() const { return color; }

    virtual char getSymbol() const = 0;
    virtual bool isValidMove(Position from, Position to,
                             vector<vector<Piece*>>& board) = 0;
};

// ================= PAWN =================
class Pawn : public Piece {
public:
    Pawn(Color c) : Piece(c) {}

    char getSymbol() const override {
        return color == Color::WHITE ? 'P' : 'p';
    }

    bool isValidMove(Position from, Position to,
                     vector<vector<Piece*>>& board) override {
        int dir = (color == Color::WHITE) ? -1 : 1;
        bool valid = from.col == to.col &&
                     board[to.row][to.col] == nullptr &&
                     to.row == from.row + dir;

        cout << "[DEBUG] Pawn move validation: "
             << (valid ? "VALID" : "INVALID") << endl;
        return valid;
    }
};

// ================= ROOK =================
class Rook : public Piece {
public:
    Rook(Color c) : Piece(c) {}

    char getSymbol() const override {
        return color == Color::WHITE ? 'R' : 'r';
    }

    bool isValidMove(Position from, Position to,
                     vector<vector<Piece*>>& board) override {
        bool valid = from.row == to.row || from.col == to.col;
        cout << "[DEBUG] Rook move validation: "
             << (valid ? "VALID" : "INVALID") << endl;
        return valid;
    }
};

// ================= KNIGHT =================
class Knight : public Piece {
public:
    Knight(Color c) : Piece(c) {}

    char getSymbol() const override {
        return color == Color::WHITE ? 'N' : 'n';
    }

    bool isValidMove(Position from, Position to,
                     vector<vector<Piece*>>& board) override {
        int dr = abs(from.row - to.row);
        int dc = abs(from.col - to.col);
        bool valid = (dr == 2 && dc == 1) || (dr == 1 && dc == 2);

        cout << "[DEBUG] Knight move validation: "
             << (valid ? "VALID" : "INVALID") << endl;
        return valid;
    }
};

// ================= BISHOP =================
class Bishop : public Piece {
public:
    Bishop(Color c) : Piece(c) {}

    char getSymbol() const override {
        return color == Color::WHITE ? 'B' : 'b';
    }

    bool isValidMove(Position from, Position to,
                     vector<vector<Piece*>>& board) override {
        bool valid = abs(from.row - to.row) == abs(from.col - to.col);
        cout << "[DEBUG] Bishop move validation: "
             << (valid ? "VALID" : "INVALID") << endl;
        return valid;
    }
};

// ================= QUEEN =================
class Queen : public Piece {
public:
    Queen(Color c) : Piece(c) {}

    char getSymbol() const override {
        return color == Color::WHITE ? 'Q' : 'q';
    }

    bool isValidMove(Position from, Position to,
                     vector<vector<Piece*>>& board) override {
        bool valid =
            from.row == to.row ||
            from.col == to.col ||
            abs(from.row - to.row) == abs(from.col - to.col);

        cout << "[DEBUG] Queen move validation: "
             << (valid ? "VALID" : "INVALID") << endl;
        return valid;
    }
};

// ================= KING =================
class King : public Piece {
public:
    King(Color c) : Piece(c) {}

    char getSymbol() const override {
        return color == Color::WHITE ? 'K' : 'k';
    }

    bool isValidMove(Position from, Position to,
                     vector<vector<Piece*>>& board) override {
        bool valid =
            abs(from.row - to.row) <= 1 &&
            abs(from.col - to.col) <= 1;

        cout << "[DEBUG] King move validation: "
             << (valid ? "VALID" : "INVALID") << endl;
        return valid;
    }
};

// ================= BOARD =================
class Board {
public:
    vector<vector<Piece*>> board;

    Board() {
        board.resize(8, vector<Piece*>(8, nullptr));
        cout << "[DEBUG] Initializing chess board\n";
        setup();
    }

    void setup() {
        cout << "[DEBUG] Setting up initial pieces\n";

        board[0][0] = new Rook(Color::BLACK);
        board[0][1] = new Knight(Color::BLACK);
        board[0][2] = new Bishop(Color::BLACK);
        board[0][3] = new Queen(Color::BLACK);
        board[0][4] = new King(Color::BLACK);

        board[7][0] = new Rook(Color::WHITE);
        board[7][1] = new Knight(Color::WHITE);
        board[7][2] = new Bishop(Color::WHITE);
        board[7][3] = new Queen(Color::WHITE);
        board[7][4] = new King(Color::WHITE);

        for (int i = 0; i < 8; i++) {
            board[1][i] = new Pawn(Color::BLACK);
            board[6][i] = new Pawn(Color::WHITE);
        }
    }

    void print() {
        cout << "\n";
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j])
                    cout << board[i][j]->getSymbol() << " ";
                else
                    cout << ". ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    bool movePiece(Position from, Position to) {
        cout << "[DEBUG] Attempting move from ("
             << from.row << "," << from.col << ") to ("
             << to.row << "," << to.col << ")\n";

        Piece* p = board[from.row][from.col];
        if (!p) {
            cout << "[DEBUG] No piece at source position\n";
            return false;
        }

        if (!p->isValidMove(from, to, board)) {
            cout << "[DEBUG] Piece rejected move\n";
            return false;
        }

        if (board[to.row][to.col]) {
            cout << "[DEBUG] Capturing piece at destination\n";
            delete board[to.row][to.col];
        }

        board[to.row][to.col] = p;
        board[from.row][from.col] = nullptr;

        cout << "[DEBUG] Move executed successfully\n";
        return true;
    }
};

// ================= GAME =================
class Game {
    Board board;
    Color turn;
    GameStatus status;

public:
    Game() : turn(Color::WHITE), status(GameStatus::ACTIVE) {
        cout << "[DEBUG] Game started. White begins.\n";
    }

    void play() {
        while (status == GameStatus::ACTIVE) {
            board.print();
            cout << ((turn == Color::WHITE) ? "White" : "Black")
                 << " move (fromRow fromCol toRow toCol): ";

            Position from, to;
            cin >> from.row >> from.col >> to.row >> to.col;

            cout << "[DEBUG] Input received\n";

            if (board.movePiece(from, to)) {
                turn = (turn == Color::WHITE) ? Color::BLACK : Color::WHITE;
                cout << "[DEBUG] Turn switched\n";
            } else {
                cout << "Invalid move. Try again.\n";
            }
        }
    }
};

// ================= MAIN =================
int main() {
    cout << "[DEBUG] Launching Chess Game\n";
    Game game;
    game.play();
    cout << "[DEBUG] Game Ended\n";
    return 0;
}
