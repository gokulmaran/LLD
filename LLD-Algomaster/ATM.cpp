#include <iostream>
using namespace std;
/*
Design ATM machine
Account: Manages account data and enforces banking rules like withdraw, deposit, and balance validation.

Card: Represents the authentication medium that validates PIN and links to an Account.

ATM: Acts as the controller that manages session flow, machine cash, and delegates behavior to states.

ATMState: Defines allowed operations at each stage of the ATM session and controls state transitions.
*/
/* ===================== Account ===================== */

class Account {
    string accountNumber;
    int balance;

public:
    Account(string accNum, int bal)
        : accountNumber(accNum), balance(bal) {}

    bool withdraw(int amount) {
        if (amount > balance)
            return false;

        balance -= amount;
        return true;
    }

    void deposit(int amount) {
        balance += amount;
    }

    int getBalance() const {
        return balance;
    }
};

/* ===================== Card ===================== */

class Card {
    int pin;
    int cardNumber;
    Account* account;

public:
    Card(int cardNo, int p, Account* acc)
        : pin(p), cardNumber(cardNo), account(acc) {}

    bool validatePin(int enteredPin) {
        return pin == enteredPin;
    }

    Account* getAccount() {
        return account;
    }
};

/* ===================== Forward Declaration ===================== */

class ATM;

/* ===================== ATM State Interface ===================== */

class ATMState {
public:
    virtual void insertCard(ATM*, Card*) = 0;
    virtual void enterPin(ATM*, int) = 0;
    virtual void withdraw(ATM*, int) = 0;
    virtual void ejectCard(ATM*) = 0;
    virtual ~ATMState() {}
};

/* ===================== ATM Context ===================== */

class IdleState;
class HasCardState;
class AuthenticatedState;

class ATM {
    ATMState* idleState;
    ATMState* hasCardState;
    ATMState* authenticatedState;

    ATMState* currentState;
    Card* currentCard;
    int totalCash;

public:
    ATM(int cash);
    ~ATM();

    void setState(ATMState* state) { currentState = state; }

    ATMState* getIdleState() { return idleState; }
    ATMState* getHasCardState() { return hasCardState; }
    ATMState* getAuthenticatedState() { return authenticatedState; }

    void setCard(Card* card) { currentCard = card; }
    Card* getCard() { return currentCard; }

    int getCash() const { return totalCash; }

    void deductCash(int amount) {
        totalCash -= amount;
    }

    /* Delegate to State */

    void insertCard(Card* card) {
        currentState->insertCard(this, card);
    }

    void enterPin(int pin) {
        currentState->enterPin(this, pin);
    }

    void withdraw(int amount) {
        currentState->withdraw(this, amount);
    }

    void ejectCard() {
        currentState->ejectCard(this);
    }
};

/* ===================== Idle State ===================== */

class IdleState : public ATMState {
public:
    void insertCard(ATM* atm, Card* card) override {
        atm->setCard(card);
        cout << "Card inserted\n";
        atm->setState(atm->getHasCardState());
    }

    void enterPin(ATM*, int) override {
        cout << "Insert card first\n";
    }

    void withdraw(ATM*, int) override {
        cout << "Insert card first\n";
    }

    void ejectCard(ATM*) override {
        cout << "No card to eject\n";
    }
};

/* ===================== HasCard State ===================== */

class HasCardState : public ATMState {
public:
    void insertCard(ATM*, Card*) override {
        cout << "Card already inserted\n";
    }

    void enterPin(ATM* atm, int pin) override {
        if (atm->getCard()->validatePin(pin)) {
            cout << "PIN correct\n";
            atm->setState(atm->getAuthenticatedState());
        } else {
            cout << "Incorrect PIN\n";
        }
    }

    void withdraw(ATM*, int) override {
        cout << "Enter PIN first\n";
    }

    void ejectCard(ATM* atm) override {
        cout << "Card ejected\n";
        atm->setCard(nullptr);
        atm->setState(atm->getIdleState());
    }
};

/* ===================== Authenticated State ===================== */

class AuthenticatedState : public ATMState {
public:
    void insertCard(ATM*, Card*) override {
        cout << "Transaction already in progress\n";
    }

    void enterPin(ATM*, int) override {
        cout << "Already authenticated\n";
    }

    void withdraw(ATM* atm, int amount) override {
        Account* acc = atm->getCard()->getAccount();

        if (amount > atm->getCash()) {
            cout << "ATM has insufficient cash\n";
            return;
        }

        if (!acc->withdraw(amount)) {
            cout << "Insufficient account balance\n";
            return;
        }

        atm->deductCash(amount);

        cout << "Withdraw successful: " << amount << endl;
        cout << "Remaining balance: " << acc->getBalance() << endl;
    }

    void ejectCard(ATM* atm) override {
        cout << "Card ejected\n";
        atm->setCard(nullptr);
        atm->setState(atm->getIdleState());
    }
};

/* ===================== ATM Constructor / Destructor ===================== */

ATM::ATM(int cash) {
    idleState = new IdleState();
    hasCardState = new HasCardState();
    authenticatedState = new AuthenticatedState();

    currentState = idleState;
    currentCard = nullptr;
    totalCash = cash;
}

ATM::~ATM() {
    delete idleState;
    delete hasCardState;
    delete authenticatedState;
}

/* ===================== Main ===================== */

int main() {
    Account acc1("101", 10000);
    Card card1(1234, 1111, &acc1);

    ATM atm(50000);

    atm.insertCard(&card1);
    atm.enterPin(1111);
    atm.withdraw(2000);
    atm.ejectCard();

    return 0;
}