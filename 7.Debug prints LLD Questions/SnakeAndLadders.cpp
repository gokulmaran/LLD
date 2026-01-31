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
        int value = (rand() % 6) + 1;
        cout << "[DEBUG] Dice rolled: " << value << endl;
        return value;
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

    void setPosition(int pos) {
        cout << "[DEBUG] " << name << " position updated: "
             << position << " -> " << pos << endl;
        position = pos;
    }
};

// ======================= BOARD =======================

class Board {
    int size;
    unordered_map<int, int> snakes;
    unordered_map<int, int> ladders;

public:
    Board(int size) : size(size) {
        cout << "[DEBUG] Board created with size " << size << endl;
    }

    void addSnake(int start, int end) {
        snakes[start] = end;
        cout << "[DEBUG] Snake added: " << start << " -> " << end << endl;
    }

    void addLadder(int start, int end) {
        ladders[start] = end;
        cout << "[DEBUG] Ladder added: " << start << " -> " << end << endl;
    }

    int getNextPosition(int pos) {
        if (snakes.count(pos)) {
            cout << "[DEBUG] Snake bite at " << pos
                 << ", sliding to " << snakes[pos] << endl;
            return snakes[pos];
        }

        if (ladders.count(pos)) {
            cout << "[DEBUG] Ladder climb at " << pos
                 << ", climbing to " << ladders[pos] << endl;
            return ladders[pos];
        }

        cout << "[DEBUG] No snake/ladder at " << pos << endl;
        return pos;
    }

    int getSize() const { return size; }
};

// ======================= GAME =======================

class Game {
    Board board;
    Dice dice;
    queue<Player*> players;
    int turn = 1;

public:
    Game(Board board) : board(board) {}

    void addPlayer(Player* player) {
        cout << "[DEBUG] Player added: " << player->getName() << endl;
        players.push(player);
    }

    void start() {
        cout << "\n[DEBUG] Game started\n\n";

        while (true) {
            Player* curr = players.front();
            players.pop();

            cout << "---------------------------------\n";
            cout << "[TURN " << turn++ << "] "
                 << curr->getName()
                 << " at position " << curr->getPosition() << endl;

            int roll = dice.roll();
            int tentativePos = curr->getPosition() + roll;

            cout << "[DEBUG] Tentative position: " << tentativePos << endl;

            if (tentativePos > board.getSize()) {
                cout << "[DEBUG] Move exceeds board size. Turn skipped.\n";
                players.push(curr);
                continue;
            }

            int finalPos = board.getNextPosition(tentativePos);
            curr->setPosition(finalPos);

            cout << curr->getName()
                 << " moved to " << finalPos << endl;

            if (finalPos == board.getSize()) {
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
