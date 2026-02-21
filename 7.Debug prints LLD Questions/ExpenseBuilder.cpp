#include <bits/stdc++.h>
using namespace std;

/* =========================
   USER
========================= */
class User {
    string id;
    string name;
    string email;

public:
    User(string id, string name, string email)
        : id(id), name(name), email(email) {}

    string getId() const { return id; }
    string getName() const { return name; }
};

/* =========================
   BALANCE SHEET
========================= */
class BalanceSheet {
    unordered_map<string, double> balances;

public:
    void addBalance(const string& userId, double amount) {
        balances[userId] += amount;
    }

    unordered_map<string, double> getBalances() const {
        return balances;
    }
};

/* =========================
   SPLIT STRATEGY (Strategy)
========================= */
class SplitStrategy {
public:
    virtual vector<double> calculate(
        double total,
        int n,
        const vector<double>& input) = 0;
    virtual ~SplitStrategy() = default;
};

class EqualSplitStrategy : public SplitStrategy {
public:
    vector<double> calculate(double total, int n,
                             const vector<double>&) override {
        return vector<double>(n, total / n);
    }
};

class ExactSplitStrategy : public SplitStrategy {
public:
    vector<double> calculate(double,
                             int,
                             const vector<double>& input) override {
        return input;
    }
};

class PercentageSplitStrategy : public SplitStrategy {
public:
    vector<double> calculate(double total, int,
                             const vector<double>& input) override {
        vector<double> result;
        for (double p : input)
            result.push_back((total * p) / 100.0);
        return result;
    }
};

/* =========================
   EXPENSE
========================= */
class Expense {
    string id;
    User* payer;
    vector<User*> participants;
    vector<double> splits;

public:
    Expense(string id, User* payer,
            vector<User*> participants,
            vector<double> splits)
        : id(id), payer(payer),
          participants(participants),
          splits(splits) {}

    User* getPayer() { return payer; }
    vector<User*> getParticipants() { return participants; }
    vector<double> getSplits() { return splits; }
};

/* =========================
   EXPENSE BUILDER (Builder)
========================= */
class ExpenseBuilder {
    string id;
    User* payer;
    vector<User*> participants;
    double total;
    SplitStrategy* strategy;
    vector<double> input;

public:
    ExpenseBuilder& setId(string id) {
        this->id = id; return *this;
    }

    ExpenseBuilder& setPayer(User* payer) {
        this->payer = payer; return *this;
    }

    ExpenseBuilder& setParticipants(vector<User*> users) {
        participants = users; return *this;
    }

    ExpenseBuilder& setTotal(double total) {
        this->total = total; return *this;
    }

    ExpenseBuilder& setStrategy(SplitStrategy* s,
                                vector<double> input = {}) {
        strategy = s;
        this->input = input;
        return *this;
    }

    Expense build() {
        auto splits = strategy->calculate(
            total, participants.size(), input);
        return Expense(id, payer, participants, splits);
    }
};

/* =========================
   EXPENSE MANAGER
========================= */
class ExpenseManager {
    unordered_map<string, BalanceSheet> balanceSheets;

public:
    void addExpense(Expense& expense) {
        User* payer = expense.getPayer();
        auto users = expense.getParticipants();
        auto splits = expense.getSplits();

        for (int i = 0; i < users.size(); i++) {
            if (users[i]->getId() == payer->getId()) continue;

            balanceSheets[payer->getId()]
                .addBalance(users[i]->getId(), splits[i]);

            balanceSheets[users[i]->getId()]
                .addBalance(payer->getId(), -splits[i]);
        }
    }

    void showBalances() {
        bool empty = true;
        for (auto& u : balanceSheets) {
            for (auto& v : u.second.getBalances()) {
                if (v.second > 0) {
                    empty = false;
                    cout << v.first << " owes "
                         << u.first << " "
                         << fixed << setprecision(2)
                         << v.second << endl;
                }
            }
        }
        if (empty) cout << "No balances\n";
    }
};

/* =========================
   COMMAND PATTERN
========================= */
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

class CreateExpenseCommand : public Command {
    ExpenseManager* manager;
    Expense expense;

public:
    CreateExpenseCommand(ExpenseManager* m, Expense e)
        : manager(m), expense(e) {}

    void execute() override {
        manager->addExpense(expense);
    }

    void undo() override {
        // Not implemented (out of scope for interview)
    }
};

/* =========================
   FACADE
========================= */
class SplitwiseFacade {
    ExpenseManager expenseManager;

public:
    ExpenseManager& getExpenseManager() {
        return expenseManager;
    }
};

/* =========================
   MAIN (Demo)
========================= */
int main() {
    User u1("u1", "A", "a@mail.com");
    User u2("u2", "B", "b@mail.com");
    User u3("u3", "C", "c@mail.com");

    EqualSplitStrategy equalStrategy;

    Expense expense = ExpenseBuilder()
        .setId("e1")
        .setPayer(&u1)
        .setParticipants({&u1, &u2, &u3})
        .setTotal(300)
        .setStrategy(&equalStrategy)
        .build();

    SplitwiseFacade app;

    CreateExpenseCommand cmd(
        &app.getExpenseManager(), expense);

    cmd.execute();
    app.getExpenseManager().showBalances();

    return 0;
}
