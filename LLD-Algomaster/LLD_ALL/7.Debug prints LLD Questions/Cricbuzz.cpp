#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ======================= PLAYER =======================

class Player {
    string name;

public:
    Player(string name) : name(name) {
        cout << "[DEBUG] Player created: " << name << endl;
    }

    string getName() const { return name; }
};

// ======================= TEAM =======================

class Team {
    string name;
    vector<Player> players;

public:
    Team(string name) : name(name) {
        cout << "[DEBUG] Team created: " << name << endl;
    }

    void addPlayer(const string& name) {
        cout << "[DEBUG] Adding player " << name << " to team " << this->name << endl;
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
        : runs(runs), wicket(wicket) {
        cout << "[DEBUG] Ball created | Runs: " << runs
             << " | Wicket: " << (wicket ? "YES" : "NO") << endl;
    }

    int getRuns() const { return runs; }
    bool isWicket() const { return wicket; }
};

// ======================= OVER =======================

class Over {
    vector<Ball> balls;

public:
    Over() {
        cout << "[DEBUG] New over started" << endl;
    }

    void addBall(const Ball& ball) {
        balls.push_back(ball);
        cout << "[DEBUG] Ball added to over | Balls in over: "
             << balls.size() << endl;
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
    Innings(Team* team) : battingTeam(team) {
        cout << "[DEBUG] Innings started for team: "
             << battingTeam->getName() << endl;
    }

    void addBall(const Ball& ball) {
        if (overs.empty() || overs.back().isComplete()) {
            overs.emplace_back();
        }

        overs.back().addBall(ball);

        totalRuns += ball.getRuns();
        if (ball.isWicket()) {
            wickets++;
            cout << "[DEBUG] WICKET! Total wickets: " << wickets << endl;
        }

        cout << "[DEBUG] Score updated: "
             << totalRuns << "/" << wickets << endl;
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
        cout << "[DEBUG] Match created between "
             << teamA.getName() << " vs " << teamB.getName() << endl;

        currentInnings = new Innings(&teamA);
    }

    ~Match() {
        cout << "[DEBUG] Match ended. Cleaning up innings" << endl;
        delete currentInnings;
    }

    void playBall(int runs, bool wicket) {
        cout << "\n[DEBUG] ---- New Ball ----" << endl;

        Ball ball(runs, wicket);
        currentInnings->addBall(ball);

        commentary.add(
            "Ball played: " + to_string(runs) +
            (wicket ? " + WICKET" : "")
        );
    }

    void showScore() {
        cout << "\n[DEBUG] ---- SCOREBOARD ----" << endl;
        cout << "Score: "
             << currentInnings->getScore()
             << " in "
             << currentInnings->getOvers()
             << " overs" << endl;
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
