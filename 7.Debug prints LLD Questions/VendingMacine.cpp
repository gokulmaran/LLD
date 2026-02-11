#include <iostream>
#include <string>
#include <vector>
#include <map>

// 1. Forward Declaration
class VendingMachine;

// 2. State Interface
class VendingState {
public:
    virtual ~VendingState() {}
    virtual void insertMoney(VendingMachine* machine, double amount) = 0;
    virtual void selectProduct(VendingMachine* machine, std::string productCode) = 0;
    virtual void dispense(VendingMachine* machine) = 0;
};

// 3. Vending Machine (Context)
class VendingMachine {
private:
    VendingState* currentState;
    double currentBalance;
    std::map<std::string, int> inventory; // Code -> Quantity
    std::map<std::string, double> prices; // Code -> Price

public:
    VendingMachine(VendingState* initialState) : currentState(initialState), currentBalance(0.0) {
        // Initialize sample inventory
        inventory["A1"] = 5; prices["A1"] = 1.5;
        inventory["B1"] = 2; prices["B1"] = 2.0;
    }

    void setState(VendingState* newState) {
        if (currentState) delete currentState;
        currentState = newState;
    }

    void addBalance(double amount) { currentBalance += amount; }
    double getBalance() { return currentBalance; }
    void resetBalance() { currentBalance = 0; }
    
    int getStock(std::string code) { return inventory[code]; }
    double getPrice(std::string code) { return prices[code]; }
    void reduceStock(std::string code) { inventory[code]--; }

    // User actions
    void insertMoney(double amount) { currentState->insertMoney(this, amount); }
    void selectProduct(std::string code) { currentState->selectProduct(this, code); }
    void dispense() { currentState->dispense(this); }
};

// 4. Concrete States
class IdleState;
class HasMoneyState;
class DispenseState;

class IdleState : public VendingState {
public:
    void insertMoney(VendingMachine* machine, double amount) override;
    void selectProduct(VendingMachine* machine, std::string code) override {
        std::cout << "[IDLE] Insert money first!\n";
    }
    void dispense(VendingMachine* machine) override {
        std::cout << "[IDLE] Insert money and select item first!\n";
    }
};

class HasMoneyState : public VendingState {
public:
    void insertMoney(VendingMachine* machine, double amount) override {
        machine->addBalance(amount);
        std::cout << "[HAS_MONEY] Added " << amount << ". Total: " << machine->getBalance() << "\n";
    }
    void selectProduct(VendingMachine* machine, std::string code) override;
    void dispense(VendingMachine* machine) override {
        std::cout << "[HAS_MONEY] Select product before dispensing.\n";
    }
};

class DispenseState : public VendingState {
public:
    void insertMoney(VendingMachine* machine, double amount) override {
        std::cout << "[DISPENSING] Please wait, currently dispensing.\n";
    }
    void selectProduct(VendingMachine* machine, std::string code) override {
        std::cout << "[DISPENSING] Already dispensing another item.\n";
    }
    void dispense(VendingMachine* machine) override;
};

// --- Implementation of Transitions ---
void IdleState::insertMoney(VendingMachine* machine, double amount) {
    machine->addBalance(amount);
    std::cout << "[IDLE -> HAS_MONEY] Money inserted: " << amount << "\n";
    machine->setState(new HasMoneyState());
}

void HasMoneyState::selectProduct(VendingMachine* machine, std::string code) {
    if (machine->getStock(code) > 0 && machine->getBalance() >= machine->getPrice(code)) {
        std::cout << "[HAS_MONEY -> DISPENSE] Product " << code << " selected.\n";
        machine->addBalance(-machine->getPrice(code));
        machine->reduceStock(code);
        machine->setState(new DispenseState());
    } else {
        std::cout << "[HAS_MONEY] Insufficient funds or Out of Stock.\n";
    }
}

void DispenseState::dispense(VendingMachine* machine) {
    std::cout << "[DISPENSE -> IDLE] Item dispensed! Remaining Change: " << machine->getBalance() << "\n";
    machine->resetBalance();
    machine->setState(new IdleState());
}

int main() {
    VendingMachine vm(new IdleState());
    
    vm.insertMoney(2.0);   // Enters HasMoneyState
    vm.selectProduct("A1"); // Enters DispenseState
    vm.dispense();          // Returns to IdleState
    
    return 0;
}
