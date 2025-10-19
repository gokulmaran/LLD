#include <iostream>
using namespace std;

/*Encapsulation Definition: Encapsulation is the process of bundling data (attributes)
and methods (functions) into a single unit called a class. It restricts
direct access to some of an object’s components, which helps protect data integrity
and prevent unintended modifications. 

Example: A BankAccount class
encapsulates the account balance and methods for depositing and withdrawing
money, ensuring that these operations are performed through controlled
interfaces. Importance: Encapsulation provides a clear separation between an
object's internal state and the outside world. It ensures that data is only accessed
and modified through defined methods, maintaining integrity and security.

Implementation: Use private access modifiers for attributes and public
access modifiers for methods that interact with these attributes.
*/

class BankAccount {
private:
    double balance; // Private attribute

public:
    // Constructor to initialize balance (optional)
    BankAccount(double initialBalance = 0.0) {
        balance = initialBalance;
    }

    // Public method to modify balance
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    // Public method to access balance
    double getBalance() const {
        return balance;
    }
};

int main() {
    BankAccount myAccount(100.0); // Initialize with 100
    myAccount.deposit(50.0);      // Deposit 50
    cout << "Balance: " << myAccount.getBalance() << endl; // Output: 150

    return 0;
}
