#include <iostream>
#include <string>
using namespace std;

//class: A class is a blueprint or template for
//creating objects. It defines a set of attributes (data) and methods (functions)
//that the created objects will have

class BankAccount {
private:
    string accountNumber;
    double balance;

public:
    // Constructor
    BankAccount(string accNum, double initialBalance) {
        accountNumber = accNum;
        balance = initialBalance;
    }

    // Deposit method
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    // Withdraw method
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
        }
    }

    // Getter for balance
    double getBalance() const {
        return balance;
    }

    // Getter for account number
    string getAccountNumber() const {
        return accountNumber;
    }
};

//Object: An object is an instance of a class. It represents a specific entity with
//concrete values for the attributes defined in the class.

int main() {
    // Creating objects (instances) of the BankAccount class
    BankAccount myAccount("123456", 500.00);
    BankAccount anotherAccount("654321", 300.00);

    // Using methods on the objects
    myAccount.deposit(150.00);
    myAccount.withdraw(50.00);
    cout << "Balance in myAccount: " << myAccount.getBalance() << endl; // Output: 600.00

    anotherAccount.withdraw(100.00);
    cout << "Balance in anotherAccount: " << anotherAccount.getBalance() << endl; // Output: 200.00

    return 0;
}
