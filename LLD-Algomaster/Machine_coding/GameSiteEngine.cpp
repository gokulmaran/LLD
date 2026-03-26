#include <bits/stdc++.h>
using namespace std;

/*
Requirements (flow)
User can do login
User can create or join the game
System should supports multiple games
game engine should maintain the game logic
player can make move and declare the winner
*/

// 👤 User
class User {
public:
    int id;
    string name;

    User(int id, string name) : id(id), name(name) {}
};

// 🎮 Player
class Player {
public:
    User user;

    Player(User u) : user(u) {}

    void makeMove() {
        cout << user.name << " makes a move\n";
    }
};

// ⚙️ Game Engine (Abstract)
class GameEngine {
public:
    virtual void runGame() = 0;
    virtual void makeMove(Player* player) = 0;
    virtual ~GameEngine() {}
};

// ❌ TicTacToe Engine
class TicTacToeEngine : public GameEngine {
public:
    void runGame() override {
        cout << "TicTacToe Game Started\n";
    }

    void makeMove(Player* player) override {
        player->makeMove();
    }
};

// 🎯 Match (IMPORTANT — contains turn logic)
class Match {
private:
    vector<Player*> players;
    GameEngine* engine;
    int turnIndex;

public:
    Match(GameEngine* eng) : engine(eng), turnIndex(0) {}

    void addPlayer(Player* p) {
        players.push_back(p);
    }

    void startMatch() {
        engine->runGame();

        // simple loop (simulate turns)
        for (int i = 0; i < 5; i++) {
            playTurn();
        }
    }

    void playTurn() {
        Player* current = players[turnIndex];

        cout << "Turn: " << current->user.name << endl;

        engine->makeMove(current);

        // 🔥 rotate turn
        turnIndex = (turnIndex + 1) % players.size();
    }
};

// 🚀 Driver
int main() {
    User u1(1, "A"), u2(2, "B");

    Player p1(u1), p2(u2);

    GameEngine* engine = new TicTacToeEngine();

    Match match(engine);

    match.addPlayer(&p1);
    match.addPlayer(&p2);

    match.startMatch();

    return 0;
}