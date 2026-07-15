##C++ Interview questinos

**Encapsulation**

**Encapsulation**

```cpp
class BankAccount {
private:
    double balance;   // hidden from outside
public:
    void deposit(double amt) { 
        if (amt > 0) 
           balance += amt; 
    }
    double getBalance() const { 
        return balance; 
    }
};
```