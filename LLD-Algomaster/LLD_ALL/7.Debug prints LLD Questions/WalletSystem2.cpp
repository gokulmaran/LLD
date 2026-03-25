#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// ==========================================
// 1. STRATEGY PATTERN: Cashback Logic
// ==========================================
class CashbackStrategy {
public:
    virtual ~CashbackStrategy() {}
    virtual double calculate(double amount) = 0;
};

class FlatCashback : public CashbackStrategy {
public:
    double calculate(double amount) override {
        double cashback = (amount >= 100) ? 5.0 : 0.0;
        cout << "[CashbackStrategy][Flat] Amount=" << amount
             << " Cashback=" << cashback << endl;
        return cashback;
    }
};

class PercentageCashback : public CashbackStrategy {
public:
    double calculate(double amount) override {
        double cashback = amount * 0.02;
        cout << "[CashbackStrategy][Percent] Amount=" << amount
             << " Cashback=" << cashback << endl;
        return cashback;
    }
};

// ==========================================
// 2. DOMAIN ENTITY: Wallet
// ==========================================
class Wallet {
private:
    string userId;
    double balance;

public:
    Wallet(string id, double bal) : userId(id), balance(bal) {
        cout << "[Wallet][Create] User=" << userId
             << " Balance=" << balance << endl;
    }

    void deposit(double amt) {
        balance += amt;
        cout << "[Wallet][Deposit] User=" << userId
             << " Amount=" << amt
             << " NewBalance=" << balance << endl;
    }

    bool withdraw(double amt) {
        cout << "[Wallet][Withdraw][Attempt] User=" << userId
             << " Amount=" << amt
             << " Balance=" << balance << endl;

        if (amt > balance) {
            cout << "[Wallet][Withdraw][FAILED] Insufficient funds\n";
            return false;
        }
        balance -= amt;
        cout << "[Wallet][Withdraw][SUCCESS] User=" << userId
             << " NewBalance=" << balance << endl;
        return true;
    }

    double getBalance() const { return balance; }
};

// ==========================================
// 3. COMMAND PATTERN: Transaction Logic
// ==========================================
class Command {
public:
    virtual ~Command() {}
    virtual bool execute() = 0;
    virtual void undo() = 0;
};

class TransferCommand : public Command {
private:
    Wallet *from, *to;
    double amount;
    bool isExecuted;

public:
    TransferCommand(Wallet* f, Wallet* t, double amt)
        : from(f), to(t), amount(amt), isExecuted(false) {
        cout << "[Command][Create] Transfer Amount=" << amount << endl;
    }

    bool execute() override {
        cout << "[Command][Execute] Transfer Start\n";
        if (from->withdraw(amount)) {
            to->deposit(amount);
            isExecuted = true;
            cout << "[Command][Execute][SUCCESS]\n";
            return true;
        }
        cout << "[Command][Execute][FAILED]\n";
        return false;
    }

    void undo() override {
        if (!isExecuted) return;

        cout << "[Command][Undo] Rolling back transfer\n";
        to->withdraw(amount);
        from->deposit(amount);
        isExecuted = false;
        cout << "[Command][Undo][DONE]\n";
    }
};

// ==========================================
// 4. SINGLETON PATTERN: Wallet Manager
// ==========================================
class WalletManager {
private:
    static WalletManager* instance;
    unordered_map<string, Wallet*> wallets;
    vector<Command*> history;
    CashbackStrategy* cashback;

    WalletManager() : cashback(new FlatCashback()) {
        cout << "[WalletManager][Init]\n";
    }

public:
    static WalletManager* getInstance() {
        if (!instance) {
            instance = new WalletManager();
        }
        return instance;
    }

    void setCashbackStrategy(CashbackStrategy* s) {
        cout << "[WalletManager][StrategyChange]\n";
        delete cashback;
        cashback = s;
    }

    void createWallet(string id, double amount) {
        cout << "[WalletManager][CreateWallet] User=" << id << endl;
        wallets[id] = new Wallet(id, amount);
    }

    void performTransfer(string fId, string tId, double amount) {
        cout << "\n[WalletManager][Transfer] From=" << fId
             << " To=" << tId
             << " Amount=" << amount << endl;

        if (!wallets.count(fId) || !wallets.count(tId)) {
            cout << "[WalletManager][Transfer][FAILED] Invalid users\n";
            return;
        }

        Command* cmd = new TransferCommand(wallets[fId], wallets[tId], amount);
        if (cmd->execute()) {
            history.push_back(cmd);

            double reward = cashback->calculate(amount);
            wallets[fId]->deposit(reward);

            cout << "[WalletManager][Transfer][SUCCESS] Cashback=" << reward << endl;
        } else {
            delete cmd;
            cout << "[WalletManager][Transfer][FAILED]\n";
        }
    }

    void undoLastTransaction() {
        cout << "\n[WalletManager][Undo]\n";
        if (history.empty()) {
            cout << "[WalletManager][Undo][FAILED] No history\n";
            return;
        }
        history.back()->undo();
        delete history.back();
        history.pop_back();
    }

    void showStatus(string id) {
        if (wallets.count(id)) {
            cout << "[WalletManager][Status] User=" << id
                 << " Balance=" << wallets[id]->getBalance() << endl;
        }
    }
};

WalletManager* WalletManager::instance = nullptr;

// ==========================================
// 5. MAIN
// ==========================================
int main() {
    WalletManager* system = WalletManager::getInstance();

    system->createWallet("Alice", 1000.0);
    system->createWallet("Bob", 500.0);

    system->performTransfer("Alice", "Bob", 200.0);
    system->showStatus("Alice");

    system->setCashbackStrategy(new PercentageCashback());
    system->performTransfer("Alice", "Bob", 100.0);
    system->showStatus("Alice");

    cout << "\n--- Undoing Last Transaction ---\n";
    system->undoLastTransaction();
    system->showStatus("Alice");

    return 0;
}
