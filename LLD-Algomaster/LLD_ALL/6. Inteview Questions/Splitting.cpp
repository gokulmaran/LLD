#include<bits/stdc++.h>
using namespace std;
//Splitwise – Full C++ LLD Code

//1️⃣ User Class
class User {
public:
    int id;
    string name;

    User(int id, string name) : id(id), name(name) {}
};

//2️⃣ Split Strategy (Strategy Pattern)
class SplitStrategy {
public:
    virtual vector<double> split(double amount,
                                 const vector<double>& values,
                                 int n) = 0;
    virtual ~SplitStrategy() {}
};

//3️⃣ Concrete Strategies
//Equal Split
class EqualSplit : public SplitStrategy {
public:
    vector<double> split(double amount,
                         const vector<double>& values,
                         int n) override {
        vector<double> res(n, amount / n);
        return res;
    }
};

//Exact Split
class ExactSplit : public SplitStrategy {
public:
    vector<double> split(double amount,
                         const vector<double>& values,
                         int n) override {
        return values; // exact amounts provided
    }
};

//Percent Split
class PercentSplit : public SplitStrategy {
public:
    vector<double> split(double amount,
                         const vector<double>& values,
                         int n) override {
        vector<double> res;
        for (double p : values)
            res.push_back((p / 100.0) * amount);
        return res;
    }
};

//4️⃣ Factory Pattern
class SplitFactory {
public:
    static SplitStrategy* getStrategy(const string& type) {
        if (type == "EQUAL") return new EqualSplit();
        if (type == "EXACT") return new ExactSplit();
        if (type == "PERCENT") return new PercentSplit();
        return nullptr;
    }
};

//5️⃣ Splitwise Service (Core Logic)
class SplitwiseService {
private:
    unordered_map<int, User*> users;
    unordered_map<int, unordered_map<int, double>> balance;

public:
    void addUser(int id, string name) {
        users[id] = new User(id, name);
    }

    void addExpense(int paidBy,
                    double amount,
                    vector<int>& participants,
                    string splitType,
                    vector<double> values) {

        int n = participants.size();
        SplitStrategy* strategy = SplitFactory::getStrategy(splitType);
        vector<double> splits = strategy->split(amount, values, n);

        for (int i = 0; i < n; i++) {
            int user = participants[i];
            if (user == paidBy) continue;

            balance[user][paidBy] += splits[i];
            balance[paidBy][user] -= splits[i];
        }

        delete strategy;
    }

    void showBalances() {
        for (auto& u : balance) {
            for (auto& v : u.second) {
                if (v.second > 0) {
                    cout << users[u.first]->name
                         << " owes "
                         << users[v.first]->name
                         << " : " << v.second << endl;
                }
            }
        }
    }
};

//6️⃣ Driver Code (Example)
int main() {
    SplitwiseService sw;

    sw.addUser(1, "Alice");
    sw.addUser(2, "Bob");
    sw.addUser(3, "Charlie");

    vector<int> users = {1, 2, 3};

    // Alice paid 300 equally
    sw.addExpense(1, 300, users, "EQUAL", {});

    sw.showBalances();
    return 0;
}

/*
🔁 Output
Bob owes Alice : 100
Charlie owes Alice : 100
*/