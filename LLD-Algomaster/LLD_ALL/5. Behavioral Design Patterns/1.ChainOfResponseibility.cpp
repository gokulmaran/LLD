#include <iostream>
using namespace std;

/* ===================== ABSTRACT HANDLER ===================== */

class CashDispenser {
protected:
    CashDispenser* nextDispenser;

public:
    CashDispenser() : nextDispenser(nullptr) {}

    void setNext(CashDispenser* next) {
        nextDispenser = next;
    }

    virtual void dispense(int amount) = 0;

    virtual ~CashDispenser() = default;
};

/* ===================== ₹2000 DISPENSER ===================== */

class Dispenser2000 : public CashDispenser {
public:
    void dispense(int amount) override {
        int count = amount / 2000;
        int remainder = amount % 2000;

        if (count > 0) {
            cout << "Dispensing " << count << " ₹2000 notes" << endl;
        }

        if (remainder > 0 && nextDispenser) {
            nextDispenser->dispense(remainder);
        }
    }
};

/* ===================== ₹500 DISPENSER ===================== */

class Dispenser500 : public CashDispenser {
public:
    void dispense(int amount) override {
        int count = amount / 500;
        int remainder = amount % 500;

        if (count > 0) {
            cout << "Dispensing " << count << " ₹500 notes" << endl;
        }

        if (remainder > 0 && nextDispenser) {
            nextDispenser->dispense(remainder);
        }
    }
};

/* ===================== ₹100 DISPENSER ===================== */

class Dispenser100 : public CashDispenser {
public:
    void dispense(int amount) override {
        int count = amount / 100;

        if (count > 0) {
            cout << "Dispensing " << count << " ₹100 notes" << endl;
        }
    }
};

/* ===================== CLIENT (MAIN) ===================== */

int main() {
    // Create handlers
    CashDispenser* d2000 = new Dispenser2000();
    CashDispenser* d500  = new Dispenser500();
    CashDispenser* d100  = new Dispenser100();

    // Chain: 2000 → 500 → 100
    d2000->setNext(d500);
    d500->setNext(d100);

    int amount = 5000;
    cout << "Withdrawing ₹" << amount << endl;

    // Start chain
    d2000->dispense(amount);

    return 0;
}
