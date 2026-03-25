#include <iostream>
using namespace std;

// ================== FORWARD DECLARATIONS ==================
class ATM;
class IdleState;
class HasCardState;
class PinVerifiedState;

// ================== CHAIN OF RESPONSIBILITY ==================

class CashHandler {
protected:
    CashHandler* next;

public:
    CashHandler() : next(nullptr) {}
    virtual ~CashHandler() { delete next; }

    void setNext(CashHandler* n) { next = n; }

    virtual void handle(int amount) {
        if (next) next->handle(amount);
        else if (amount > 0)
            cout << "[ERROR] Cannot dispense remaining $" << amount << endl;
    }
};

class Dollar100Handler : public CashHandler {
public:
    void handle(int amount) override {
        if (amount >= 100) {
            int cnt = amount / 100;
            cout << "[DISPENSE] " << cnt << " x $100\n";
            CashHandler::handle(amount % 100);
        } else {
            CashHandler::handle(amount);
        }
    }
};

class Dollar50Handler : public CashHandler {
public:
    void handle(int amount) override {
        if (amount >= 50) {
            int cnt = amount / 50;
            cout << "[DISPENSE] " << cnt << " x $50\n";
            CashHandler::handle(amount % 50);
        } else {
            CashHandler::handle(amount);
        }
    }
};

class Dollar10Handler : public CashHandler {
public:
    void handle(int amount) override {
        if (amount >= 10) {
            int cnt = amount / 10;
            cout << "[DISPENSE] " << cnt << " x $10\n";
            CashHandler::handle(amount % 10);
        } else {
            CashHandler::handle(amount);
        }
    }
};

// ================== STATE INTERFACE ==================

class ATMState {
public:
    virtual ~ATMState() {}
    virtual void insertCard(ATM*) = 0;
    virtual void authenticatePin(ATM*, int) = 0;
    virtual void withdrawCash(ATM*, int) = 0;
    virtual void ejectCard(ATM*) = 0;
};

// ================== CONTEXT ==================

class ATM {
    ATMState* state;
    int vaultCash;
    CashHandler* dispenser;

public:
    ATM(ATMState* initState, int cash) : state(initState), vaultCash(cash) {
        cout << "[ATM] Initializing ATM with $" << cash << endl;

        dispenser = new Dollar100Handler();
        CashHandler* h50 = new Dollar50Handler();
        CashHandler* h10 = new Dollar10Handler();

        dispenser->setNext(h50);
        h50->setNext(h10);
    }

    ~ATM() {
        delete state;
        delete dispenser;
    }

    void setState(ATMState* s) {
        cout << "[ATM] State transition\n";
        delete state;
        state = s;
    }

    int getCash() { return vaultCash; }
    void deductCash(int amt) { vaultCash -= amt; }

    void dispense(int amt) {
        cout << "[ATM] Dispensing $" << amt << endl;
        dispenser->handle(amt);
    }

    // Delegation
    void insertCard() { state->insertCard(this); }
    void enterPin(int pin) { state->authenticatePin(this, pin); }
    void withdraw(int amt) { state->withdrawCash(this, amt); }
    void ejectCard() { state->ejectCard(this); }
};

// ================== CONCRETE STATES ==================

class IdleState : public ATMState {
public:
    void insertCard(ATM* atm) override;
    void authenticatePin(ATM*, int) override;
    void withdrawCash(ATM*, int) override;
    void ejectCard(ATM*) override;
};

class HasCardState : public ATMState {
public:
    void insertCard(ATM*) override;
    void authenticatePin(ATM*, int) override;
    void withdrawCash(ATM*, int) override;
    void ejectCard(ATM*) override;
};

class PinVerifiedState : public ATMState {
public:
    void insertCard(ATM*) override;
    void authenticatePin(ATM*, int) override;
    void withdrawCash(ATM*, int) override;
    void ejectCard(ATM*) override;
};

// ================== STATE IMPLEMENTATIONS ==================

void IdleState::insertCard(ATM* atm) {
    cout << "[STATE] IDLE → HAS_CARD\n";
    atm->setState(new HasCardState());
}

void IdleState::authenticatePin(ATM*, int) {
    cout << "[ERROR] Insert card first\n";
}

void IdleState::withdrawCash(ATM*, int) {
    cout << "[ERROR] Insert card first\n";
}

void IdleState::ejectCard(ATM*) {
    cout << "[ERROR] No card to eject\n";
}

void HasCardState::insertCard(ATM*) {
    cout << "[ERROR] Card already inserted\n";
}

void HasCardState::authenticatePin(ATM* atm, int pin) {
    cout << "[DEBUG] PIN entered: " << pin << endl;
    if (pin == 1234) {
        cout << "[STATE] HAS_CARD → PIN_VERIFIED\n";
        atm->setState(new PinVerifiedState());
    } else {
        cout << "[ERROR] Invalid PIN\n";
    }
}

void HasCardState::withdrawCash(ATM*, int) {
    cout << "[ERROR] Enter PIN first\n";
}

void HasCardState::ejectCard(ATM* atm) {
    cout << "[STATE] HAS_CARD → IDLE\n";
    atm->setState(new IdleState());
}

void PinVerifiedState::insertCard(ATM*) {
    cout << "[ERROR] Card already inserted\n";
}

void PinVerifiedState::authenticatePin(ATM*, int) {
    cout << "[INFO] PIN already verified\n";
}

void PinVerifiedState::withdrawCash(ATM* atm, int amt) {
    cout << "[WITHDRAW] Requested $" << amt << endl;

    if (amt <= atm->getCash()) {
        atm->dispense(amt);
        atm->deductCash(amt);
        cout << "[SUCCESS] Cash withdrawn. Remaining: $" << atm->getCash() << endl;
    } else {
        cout << "[ERROR] Insufficient ATM funds\n";
    }
}

void PinVerifiedState::ejectCard(ATM* atm) {
    cout << "[STATE] PIN_VERIFIED → IDLE\n";
    atm->setState(new IdleState());
}

// ================== MAIN ==================

int main() {
    ATM atm(new IdleState(), 2000);

    atm.insertCard();
    atm.enterPin(1234);

    cout << "\n--- Transaction: $260 ---\n";
    atm.withdraw(260);

    atm.ejectCard();
    return 0;
}
