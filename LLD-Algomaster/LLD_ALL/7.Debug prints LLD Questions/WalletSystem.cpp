#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

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
    double calculate(double amount) override { return (amount >= 100) ? 5.0 : 0.0; }
};

class PercentageCashback : public CashbackStrategy {
public:
    double calculate(double amount) override { return amount * 0.02; } // 2% Cashback
};

// ==========================================
// 2. DOMAIN ENTITY: Wallet
// ==========================================
class Wallet {
private:
    std::string userId;
    double balance;
public:
    Wallet(std::string id, double bal) : userId(id), balance(bal) {}
    void deposit(double amt) { balance += amt; }
    bool withdraw(double amt) {
        if (amt > balance) return false;
        balance -= amt;
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
        : from(f), to(t), amount(amt), isExecuted(false) {}

    bool execute() override {
        if (from->withdraw(amount)) {
            to->deposit(amount);
            isExecuted = true;
            return true;
        }
        return false;
    }

    void undo() override {
        if (isExecuted) {
            to->withdraw(amount);
            from->deposit(amount);
            isExecuted = false;
            std::cout << "Transaction Undone: Refunded " << amount << " to " << from->getBalance() << "\n";
        }
    }
};

// ==========================================
// 4. SINGLETON PATTERN: Wallet Manager
// ==========================================
class WalletManager {
private:
    static WalletManager* instance;
    std::unordered_map<std::string, Wallet*> wallets;
    std::vector<Command*> history;
    CashbackStrategy* cashback;

    WalletManager() : cashback(new FlatCashback()) {} // Private Constructor

public:
    static WalletManager* getInstance() {
        if (!instance) instance = new WalletManager();
        return instance;
    }

    void setCashbackStrategy(CashbackStrategy* s) {
        delete cashback;
        cashback = s;
    }

    void createWallet(std::string id, double amount) {
        wallets[id] = new Wallet(id, amount);
    }

    void performTransfer(std::string fId, std::string tId, double amount) {
        if (!wallets.count(fId) || !wallets.count(tId)) return;

        Command* cmd = new TransferCommand(wallets[fId], wallets[tId], amount);
        if (cmd->execute()) {
            history.push_back(cmd);
            double reward = cashback->calculate(amount);
            wallets[fId]->deposit(reward);
            std::cout << "Transfer Successful! Cashback awarded: " << reward << "\n";
        } else {
            delete cmd;
            std::cout << "Transfer Failed: Insufficient Funds.\n";
        }
    }

    void undoLastTransaction() {
        if (!history.empty()) {
            history.back()->undo();
            delete history.back();
            history.pop_back();
        }
    }

    void showStatus(std::string id) {
        if (wallets.count(id))
            std::cout << "User: " << id << " Balance: " << wallets[id]->getBalance() << "\n";
    }
};

WalletManager* WalletManager::instance = nullptr;

// ==========================================
// 5. MAIN (2026 Simulation)
// ==========================================
int main() {
    WalletManager* system = WalletManager::getInstance();

    system->createWallet("Alice", 1000.0);
    system->createWallet("Bob", 500.0);

    // 1. Successful Transfer with Flat Cashback
    system->performTransfer("Alice", "Bob", 200.0);
    system->showStatus("Alice");

    // 2. Change to Percentage Cashback (Strategy Pattern)
    system->setCashbackStrategy(new PercentageCashback());
    system->performTransfer("Alice", "Bob", 100.0);
    system->showStatus("Alice");

    // 3. Rollback (Command Pattern Undo)
    std::cout << "--- Undoing Last Action ---\n";
    system->undoLastTransaction();
    system->showStatus("Alice");

    return 0;
}
