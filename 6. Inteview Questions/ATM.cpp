#include <iostream>
#include <string>
using namespace std;

/* ===================== ENUMS ===================== */

enum class TransactionType {
    CASH_WITHDRAWAL,
    BALANCE_ENQUIRY
};

enum class CardStatus {
    ACTIVE,
    BLOCKED
};

/* ===================== BANK ACCOUNT ===================== */

class BankAccount {
    int balance;

public:
    BankAccount(int bal) : balance(bal) {}

    int getBalance() const {
        return balance;
    }

    bool debit(int amount) {
        if (balance < amount) return false;
        balance -= amount;
        return true;
    }
};

/* ===================== ATM CARD ===================== */

class ATMCard {
    string cardNumber;
    int pin;
    CardStatus status;
    BankAccount* account;

public:
    ATMCard(string num, int p, BankAccount* acc)
        : cardNumber(num), pin(p),
          status(CardStatus::ACTIVE), account(acc) {}

    bool validatePin(int enteredPin) const {
        return pin == enteredPin;
    }

    bool isActive() const {
        return status == CardStatus::ACTIVE;
    }

    BankAccount* getAccount() const {
        return account;
    }
};

/* ===================== CASH WITHDRAW PROCESSOR ===================== */

class CashWithdrawProcessor {
protected:
    CashWithdrawProcessor* next;

public:
    CashWithdrawProcessor(CashWithdrawProcessor* n) : next(n) {}
    virtual void withdraw(int amount) = 0;
};

class TwoThousandProcessor : public CashWithdrawProcessor {
public:
    TwoThousandProcessor(CashWithdrawProcessor* n)
        : CashWithdrawProcessor(n) {}

    void withdraw(int amount) override {
        int notes = amount / 2000;
        if (notes > 0)
            cout << "2000 x " << notes << endl;

        int rem = amount % 2000;
        if (rem && next) next->withdraw(rem);
    }
};

class FiveHundredProcessor : public CashWithdrawProcessor {
public:
    FiveHundredProcessor(CashWithdrawProcessor* n)
        : CashWithdrawProcessor(n) {}

    void withdraw(int amount) override {
        int notes = amount / 500;
        if (notes > 0)
            cout << "500 x " << notes << endl;

        int rem = amount % 500;
        if (rem && next) next->withdraw(rem);
    }
};

class OneHundredProcessor : public CashWithdrawProcessor {
public:
    OneHundredProcessor(CashWithdrawProcessor* n)
        : CashWithdrawProcessor(n) {}

    void withdraw(int amount) override {
        int notes = amount / 100;
        if (notes > 0)
            cout << "100 x " << notes << endl;
    }
};

/* ===================== ATM STATE ===================== */

class ATM;

class ATMState {
public:
    virtual void insertCard(ATM*) {}
    virtual void enterPin(ATM*, int) {}
    virtual void selectOperation(ATM*, TransactionType) {}
    virtual void withdrawCash(ATM*, int) {}
    virtual void checkBalance(ATM*) {}
    virtual ~ATMState() {}
};

/* ===================== ATM ===================== */

class ATM {
    ATMState* state;
    ATMCard* card;

public:
    ATM(ATMState* initialState)
        : state(initialState), card(nullptr) {}

    void setState(ATMState* s) {
        state = s;
    }

    void setCard(ATMCard* c) {
        card = c;
    }

    ATMCard* getCard() {
        return card;
    }

    void insertCard() { state->insertCard(this); }
    void enterPin(int pin) { state->enterPin(this, pin); }
    void selectOperation(TransactionType type) {
        state->selectOperation(this, type);
    }
    void withdrawCash(int amount) {
        state->withdrawCash(this, amount);
    }
    void checkBalance() {
        state->checkBalance(this);
    }
};

/* ===================== STATES ===================== */

class IdleState : public ATMState {
public:
    void insertCard(ATM* atm) override;
};

class HasCardState : public ATMState {
public:
    void enterPin(ATM* atm, int pin) override;
};

class SelectOperationState : public ATMState {
public:
    void selectOperation(ATM* atm, TransactionType type) override;
};

class CashWithdrawalState : public ATMState {
public:
    void withdrawCash(ATM* atm, int amount) override;
};

class BalanceCheckState : public ATMState {
public:
    void checkBalance(ATM* atm) override;
};

/* ===================== STATE IMPLEMENTATIONS ===================== */

void IdleState::insertCard(ATM* atm) {
    cout << "Card Inserted\n";
    atm->setState(new HasCardState());
}

void HasCardState::enterPin(ATM* atm, int pin) {
    if (atm->getCard()->validatePin(pin)) {
        cout << "PIN Verified\n";
        atm->setState(new SelectOperationState());
    } else {
        cout << "Invalid PIN\n";
        atm->setState(new IdleState());
    }
}

void SelectOperationState::selectOperation(ATM* atm, TransactionType type) {
    if (type == TransactionType::CASH_WITHDRAWAL)
        atm->setState(new CashWithdrawalState());
    else
        atm->setState(new BalanceCheckState());
}

void CashWithdrawalState::withdrawCash(ATM* atm, int amount) {
    BankAccount* acc = atm->getCard()->getAccount();

    if (!acc->debit(amount)) {
        cout << "Insufficient Balance\n";
        atm->setState(new IdleState());
        return;
    }

    CashWithdrawProcessor* processor =
        new TwoThousandProcessor(
            new FiveHundredProcessor(
                new OneHundredProcessor(nullptr)));

    processor->withdraw(amount);
    cout << "Please collect your cash\n";
    atm->setState(new IdleState());
}

void BalanceCheckState::checkBalance(ATM* atm) {
    cout << "Balance: "
         << atm->getCard()->getAccount()->getBalance()
         << endl;
    atm->setState(new IdleState());
}

/* ===================== MAIN ===================== */

int main() {
    BankAccount account(10000);
    ATMCard card("1234-5678", 1234, &account);

    ATM atm(new IdleState());
    atm.setCard(&card);

    atm.insertCard();
    atm.enterPin(1234);
    atm.selectOperation(TransactionType::CASH_WITHDRAWAL);
    atm.withdrawCash(3600);

    return 0;
}
