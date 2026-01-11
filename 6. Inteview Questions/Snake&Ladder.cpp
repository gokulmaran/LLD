#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

// ======================= DICE =======================

class Dice {
public:
    int roll() {
        return (rand() % 6) + 1;
    }
};

// ======================= PLAYER =======================

class Player {
    string name;
    int position;

public:
    Player(string name) : name(name), position(0) {}

    string getName() const { return name; }
    int getPosition() const { return position; }
    void setPosition(int pos) { position = pos; }
};

// ======================= BOARD =======================

class Board {
    int size;
    unordered_map<int, int> snakes;
    unordered_map<int, int> ladders;

public:
    Board(int size) : size(size) {}

    void addSnake(int start, int end) {
        snakes[start] = end;
    }

    void addLadder(int start, int end) {
        ladders[start] = end;
    }

    int getNextPosition(int pos) {
        if (snakes.count(pos)) {
            cout << "🐍 Snake! ";
            return snakes[pos];
        }
        if (ladders.count(pos)) {
            cout << "🪜 Ladder! ";
            return ladders[pos];
        }
        return pos;
    }

    int getSize() const {
        return size;
    }
};

// ======================= GAME =======================

class Game {
    Board board;
    Dice dice;
    queue<Player*> players;

public:
    Game(Board board) : board(board) {}

    void addPlayer(Player* player) {
        players.push(player);
    }

    void start() {
        while (true) {
            Player* curr = players.front();
            players.pop();

            int roll = dice.roll();
            cout << curr->getName() << " rolled " << roll << " ";

            int nextPos = curr->getPosition() + roll;

            if (nextPos > board.getSize()) {
                cout << "(invalid move)\n";
                players.push(curr);
                continue;
            }

            nextPos = board.getNextPosition(nextPos);
            curr->setPosition(nextPos);

            cout << "-> moved to " << nextPos << endl;

            if (nextPos == board.getSize()) {
                cout << "\n🎉 " << curr->getName() << " WINS! 🎉\n";
                break;
            }

            players.push(curr);
        }
    }
};

// ======================= MAIN =======================

int main() {
    srand(time(nullptr));

    Board board(100);

    // Snakes
    board.addSnake(99, 10);
    board.addSnake(70, 40);
    board.addSnake(52, 28);

    // Ladders
    board.addLadder(5, 25);
    board.addLadder(22, 41);
    board.addLadder(46, 90);

    Player p1("Gokul");
    Player p2("Rahul");

    Game game(board);
    game.addPlayer(&p1);
    game.addPlayer(&p2);

    game.start();
    return 0;
}
