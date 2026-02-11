#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ======================= PLAYER =======================

class Player {
    string name;

public:
    Player(string name) : name(name) {}
    string getName() const { return name; }
};

// ======================= TEAM =======================

class Team {
    string name;
    vector<Player> players;

public:
    Team(string name) : name(name) {}

    void addPlayer(const string& name) {
        players.emplace_back(name);
    }

    string getName() const { return name; }
};

// ======================= BALL =======================

class Ball {
    int runs;
    bool wicket;

public:
    Ball(int runs, bool wicket)
        : runs(runs), wicket(wicket) {}

    int getRuns() const { return runs; }
    bool isWicket() const { return wicket; }
};

// ======================= OVER =======================

class Over {
    vector<Ball> balls;

public:
    void addBall(const Ball& ball) {
        balls.push_back(ball);
    }

    bool isComplete() const {
        return balls.size() == 6;
    }

    const vector<Ball>& getBalls() const {
        return balls;
    }
};

// ======================= INNINGS =======================

class Innings {
    Team* battingTeam;
    vector<Over> overs;
    int totalRuns = 0;
    int wickets = 0;

public:
    Innings(Team* team) : battingTeam(team) {}

    void addBall(const Ball& ball) {
        if (overs.empty() || overs.back().isComplete()) {
            overs.emplace_back();
        }

        overs.back().addBall(ball);
        totalRuns += ball.getRuns();
        if (ball.isWicket()) wickets++;
    }

    int getRuns() const { return totalRuns; }
    int getWickets() const { return wickets; }
    int getOvers() const { return overs.size(); }

    string getScore() const {
        return to_string(totalRuns) + "/" + to_string(wickets);
    }
};

// ======================= COMMENTARY =======================

class Commentary {
public:
    void add(const string& text) {
        cout << "🗣 " << text << endl;
    }
};

// ======================= MATCH =======================

class Match {
    Team teamA, teamB;
    Innings* currentInnings;
    Commentary commentary;

public:
    Match(Team a, Team b)
        : teamA(a), teamB(b) {
        currentInnings = new Innings(&teamA);
    }

    ~Match() {
        delete currentInnings;
    }

    void playBall(int runs, bool wicket) {
        Ball ball(runs, wicket);
        currentInnings->addBall(ball);

        commentary.add(
            "Ball played: " + to_string(runs) + " runs"
        );
    }

    void showScore() {
        cout << "Score: "
             << currentInnings->getScore()
             << " in "
             << currentInnings->getOvers()
             << " overs\n";
    }
};

// ======================= MAIN =======================

int main() {
    Team india("India");
    india.addPlayer("Rohit");
    india.addPlayer("Virat");

    Team australia("Australia");
    australia.addPlayer("Warner");
    australia.addPlayer("Smith");

    Match match(india, australia);

    match.playBall(1, false);
    match.playBall(4, false);
    match.playBall(0, true);
    match.playBall(6, false);

    match.showScore();

    return 0;
}
