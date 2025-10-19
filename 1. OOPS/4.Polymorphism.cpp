#include <iostream>
using namespace std;

/*Polymorphism Definition: Polymorphism enables objects of different classes to
be treated as objects of a common superclass. It allows methods to be used
interchangeably, and the specific method that gets called depends on the object’s
actual class.*/

// Base class
class BankAccount {
public:
    // Virtual function allows overriding in derived classes
    virtual void calculateInterest() {
        cout << "Calculating interest for bank account" << endl;
    }

    // Virtual destructor (good practice for polymorphism)
    virtual ~BankAccount() {}
};

// Derived class: SavingsAccount
class SavingsAccount : public BankAccount {
public:
    void calculateInterest() override {
        cout << "Calculating interest for savings account" << endl;
    }
};

// Derived class: CheckingAccount
class CheckingAccount : public BankAccount {
public:
    void calculateInterest() override {
        cout << "No interest for checking account" << endl;
    }
};

int main() {
    // Polymorphic behavior using base class pointers
    BankAccount* account1 = new SavingsAccount();
    BankAccount* account2 = new CheckingAccount();

    account1->calculateInterest(); // Output: Calculating interest for savings account
    account2->calculateInterest(); // Output: No interest for checking account

    // Clean up
    delete account1;
    delete account2;

    return 0;
}
