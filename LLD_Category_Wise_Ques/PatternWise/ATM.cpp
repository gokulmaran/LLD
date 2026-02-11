#include <iostream>
#include <string>

// --- NEW: Chain of Responsibility for Cash Dispensing ---
class CashHandler {
protected:
    CashHandler* nextHandler;
public:
    CashHandler() : nextHandler(nullptr) {}
    virtual ~CashHandler() { delete nextHandler; }
    
    void setNextHandler(CashHandler* next) { nextHandler = next; }
    
    virtual void handle(int amount) {
        if (nextHandler) nextHandler->handle(amount);
        else if (amount > 0) std::cout << "Error: Cannot dispense the remaining $" << amount << " (No matching denominations).\n";
    }
};

class Dollar100Handler : public CashHandler {
public:
    void handle(int amount) override {
        if (amount >= 100) {
            int num = amount / 100;
            int remainder = amount % 100;
            std::cout << "Dispensing " << num << " x $100 notes\n";
            if (remainder > 0) CashHandler::handle(remainder);
        } else {
            CashHandler::handle(amount);
        }
    }
};

class Dollar50Handler : public CashHandler {
public:
    void handle(int amount) override {
        if (amount >= 50) {
            int num = amount / 50;
            int remainder = amount % 50;
            std::cout << "Dispensing " << num << " x $50 notes\n";
            if (remainder > 0) CashHandler::handle(remainder);
        } else {
            CashHandler::handle(amount);
        }
    }
};

class Dollar10Handler : public CashHandler {
public:
    void handle(int amount) override {
        if (amount >= 10) {
            int num = amount / 10;
            int remainder = amount % 10;
            std::cout << "Dispensing " << num << " x $10 notes\n";
            if (remainder > 0) CashHandler::handle(remainder);
        } else {
            CashHandler::handle(amount);
        }
    }
};

// --- Existing State Pattern Logic ---

class ATM;

class ATMState {
public:
    virtual ~ATMState() {}
    virtual void insertCard(ATM* atm) = 0;
    virtual void authenticatePin(ATM* atm, int pin) = 0;
    virtual void withdrawCash(ATM* atm, int amount) = 0; // Changed double to int for easier CoR logic
    virtual void ejectCard(ATM* atm) = 0;
};

class ATM {
private:
    ATMState* currentState;
    int cashVaultBalance;
    CashHandler* dispenserChain; // CoR Chain Start

public:
    ATM(ATMState* initialState, int initialCash) 
        : currentState(initialState), cashVaultBalance(initialCash) {
        
        // Initialize the Chain
        dispenserChain = new Dollar100Handler();
        CashHandler* h50 = new Dollar50Handler();
        CashHandler* h10 = new Dollar10Handler();
        
        dispenserChain->setNextHandler(h50);
        h50->setNextHandler(h10);
    }

    ~ATM() { 
        delete currentState; 
        delete dispenserChain; 
    }

    void setState(ATMState* newState) {
        if (currentState) delete currentState;
        currentState = newState;
    }

    int getVaultBalance() { return cashVaultBalance; }
    void deductCash(int amount) { cashVaultBalance -= amount; }
    
    // Trigger the CoR Chain
    void dispenseFromChain(int amount) { dispenserChain->handle(amount); }

    void insertCard() { currentState->insertCard(this); }
    void enterPin(int pin) { currentState->authenticatePin(this, pin); }
    void withdraw(int amount) { currentState->withdrawCash(this, amount); }
};

// --- Concrete States Implementation ---

class IdleState : public ATMState {
public:
    void insertCard(ATM* atm) override;
    void authenticatePin(ATM* atm, int pin) override { std::cout << "Insert card first.\n"; }
    void withdrawCash(ATM* atm, int amount) override { std::cout << "Insert card first.\n"; }
    void ejectCard(ATM* atm) override { std::cout << "No card to eject.\n"; }
};

class HasCardState : public ATMState {
public:
    void insertCard(ATM* atm) override { std::cout << "Card already inserted.\n"; }
    void authenticatePin(ATM* atm, int pin) override;
    void withdrawCash(ATM* atm, int amount) override { std::cout << "Enter PIN first.\n"; }
    void ejectCard(ATM* atm) override;
};

class PinVerifiedState : public ATMState {
public:
    void insertCard(ATM* atm) override { std::cout << "Card already inserted.\n"; }
    void authenticatePin(ATM* atm, int pin) override { std::cout << "Already verified.\n"; }
    void withdrawCash(ATM* atm, int amount) override;
    void ejectCard(ATM* atm) override;
};

// Transitions
// void IdleState::insertCard(ATM* atm) {
//     std::cout << "[IDLE -> HAS_CARD] Card detected.\n";
//     // Using a simple state switch (In a real LLD, avoid 'new' inside states if possible, but keeping it for your raw pointer requirement)
// }

// Defining these outside because they need classes to be fully defined
//void IdleState::insertCard(ATM* atm); 
// Note: In your specific structure, ensure the order of implementation allows setState with new objects.

void PinVerifiedState::withdrawCash(ATM* atm, int amount) {
    if (amount <= atm->getVaultBalance()) {
        std::cout << "Processing withdrawal for $" << amount << "...\n";
        
        // --- USING THE CHAIN OF RESPONSIBILITY HERE ---
        atm->dispenseFromChain(amount);
        
        atm->deductCash(amount);
        std::cout << "Withdrawal successful. Current Vault: $" << atm->getVaultBalance() << "\n";
    } else {
        std::cout << "Insufficient ATM funds.\n";
    }
}

// Logic implementations for transition (Simplified for brevity)
void IdleState::insertCard(ATM* atm) { atm->setState(new HasCardState()); }
void HasCardState::authenticatePin(ATM* atm, int pin) { if(pin==1234) atm->setState(new PinVerifiedState()); }
void HasCardState::ejectCard(ATM* atm) { atm->setState(new IdleState()); }
void PinVerifiedState::ejectCard(ATM* atm) { atm->setState(new IdleState()); }

int main() {
    ATM myATM(new IdleState(), 2000);

    myATM.insertCard();
    myATM.enterPin(1234);
    
    std::cout << "--- Transaction 1 ($260) ---\n";
    myATM.withdraw(260); // Should use 2x100, 1x50, 1x10
    
    return 0;
}
