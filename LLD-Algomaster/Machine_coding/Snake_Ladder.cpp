#include <bits/stdc++.h>
using namespace std;

/*Snake and ladder
1. Multiple players can play
2. Dice generates random number (1–6)
3. Player moves based on dice roll
4. Snakes move player down, ladders move player up
5. Player must reach exactly last cell (100) to win
6. Game handles turn rotation and declares winner

class Player:
  - string name
  - int position
  + move(int steps)

class Dice:
  + roll()

class Board:
  - int size
  - unordered_map<int,int> snakes
  - unordered_map<int,int> ladders
  + addSnake()
  + addLadder()
  + getFinalPosition()

class Game:
  - queue<Player*>
  - Board
  - Dice
  + setup()
  + startGame()
*/

// 🎯 Player
class Player {
public:
    string name;
    int position;

    Player(string n) : name(n), position(0) {}

    void move(int steps) {
        position += steps;
    }
};

// 🎲 Dice
class Dice {
public:
    int roll() {
        return rand() % 6 + 1;
    }
};

// 🐍 Board
class Board {
public:
    int size;
    unordered_map<int, int> snakes;
    unordered_map<int, int> ladders;

    Board(int n) : size(n) {}

    void addSnake(int start, int end) {
        snakes[start] = end;
    }

    void addLadder(int start, int end) {
        ladders[start] = end;
    }

    int getFinalPosition(int pos) {
        if (snakes.count(pos)) return snakes[pos];
        if (ladders.count(pos)) return ladders[pos];
        return pos;
    }
};

// 🎮 Game
class Game {
private:
    queue<Player*> players;
    Board board;
    Dice dice;

public:
    Game(vector<string> names, int boardSize) : board(boardSize) {
        for (auto &name : names) {
            players.push(new Player(name));
        }
    }

    void setup() {
        // snakes
        board.addSnake(99, 10);
        board.addSnake(70, 50);

        // ladders
        board.addLadder(5, 25);
        board.addLadder(40, 80);
    }

    void startGame() {
        while (true) {
            Player* curr = players.front();
            players.pop();

            int roll = dice.roll();
            cout << curr->name << " rolled " << roll << endl;

            int newPos = curr->position + roll;

            if (newPos <= board.size) {
                newPos = board.getFinalPosition(newPos);
                curr->position = newPos;
            }

            cout << curr->name << " at " << curr->position << endl;

            if (curr->position == board.size) {
                cout << curr->name << " wins!\n";
                break;
            }

            players.push(curr);
        }
    }
};

// 🚀 Driver
int main() {
    srand(time(0));

    vector<string> players = {"A", "B"};
    Game game(players, 100);

    game.setup();
    game.startGame();

    return 0;
}