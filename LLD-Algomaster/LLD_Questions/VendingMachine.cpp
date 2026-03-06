#include <bits/stdc++.h>
using namespace std;
/*
Design vending machine
product --> should have name and price
inventory --> inventory should handle the addProducts, product is available, get product,reduce stock
Vending machine --> Vending machine should have the states like insert money, select product, dispense the product
*/

//product
#include <iostream>
#include <unordered_map>
using namespace std;

class Product {
    string name;
    int price;

public:
    Product() {}
    Product(string name, int price) : name(name), price(price) {}

    string getName() const { return name; }
    int getPrice() const { return price; }
};

class Inventory {
    unordered_map<string, pair<Product, int>> m;

public:
    void addProduct(Product product, int quantity) {
        m[product.getName()] = {product, quantity};
    }

    bool isAvailable(string name) {
        return m.count(name) && m[name].second > 0;
    }

    Product getProduct(string name) {
        return m[name].first;
    }

    void reduceStock(string name) {
        m[name].second--;
    }
};

class VendingMachine;

// ===== State Interface =====
class VendingState {
public:
    virtual void selectProduct(VendingMachine*, string) = 0;
    virtual void insertMoney(VendingMachine*, int) = 0;
    virtual void dispense(VendingMachine*) = 0;
    virtual void cancel(VendingMachine*) = 0;
    virtual ~VendingState() {}
};

// ===== Vending Machine =====
class IdleState;
class HasMoneyState;
class DispenseState;

class VendingMachine {
    VendingState* idleState;
    VendingState* hasMoneyState;
    VendingState* dispenseState;

    VendingState* currentState;

    Inventory inventory;
    string selectedProduct;
    int balance;

public:
    VendingMachine();
    ~VendingMachine();

    // State getters
    VendingState* getIdleState() { return idleState; }
    VendingState* getHasMoneyState() { return hasMoneyState; }
    VendingState* getDispenseState() { return dispenseState; }

    void setState(VendingState* state) { currentState = state; }

    void setSelectedProduct(string name) { selectedProduct = name; }
    string getSelectedProduct() { return selectedProduct; }

    void addBalance(int amount) { balance += amount; }
    int getBalance() { return balance; }
    void resetBalance() { balance = 0; }

    Inventory& getInventory() { return inventory; }

    // Delegation
    void selectProduct(string name) {
        currentState->selectProduct(this, name);
    }

    void insertMoney(int amount) {
        currentState->insertMoney(this, amount);
    }

    void dispense() {
        currentState->dispense(this);
    }

    void cancel() {
        currentState->cancel(this);
    }
};

// ===== Idle State =====
class IdleState : public VendingState {
public:
    void selectProduct(VendingMachine* vm, string name) override {
        if (!vm->getInventory().isAvailable(name)) {
            cout << "Product not available\n";
            return;
        }

        vm->setSelectedProduct(name);
        cout << "Selected: " << name << endl;

        vm->setState(vm->getHasMoneyState());
    }

    void insertMoney(VendingMachine*, int) override {
        cout << "Select product first\n";
    }

    void dispense(VendingMachine*) override {
        cout << "Select product first\n";
    }

    void cancel(VendingMachine*) override {
        cout << "Nothing to cancel\n";
    }
};

// ===== HasMoney State =====
class HasMoneyState : public VendingState {
public:
    void selectProduct(VendingMachine*, string) override {
        cout << "Product already selected\n";
    }

    void insertMoney(VendingMachine* vm, int amount) override {
        vm->addBalance(amount);
        cout << "Inserted: " << amount << endl;

        string name = vm->getSelectedProduct();
        Product p = vm->getInventory().getProduct(name);

        if (vm->getBalance() >= p.getPrice()) {
            vm->setState(vm->getDispenseState());
        }
    }

    void dispense(VendingMachine*) override {
        cout << "Insufficient money\n";
    }

    void cancel(VendingMachine* vm) override {
        cout << "Returning: " << vm->getBalance() << endl;
        vm->resetBalance();
        vm->setState(vm->getIdleState());
    }
};

// ===== Dispense State =====
class DispenseState : public VendingState {
public:
    void selectProduct(VendingMachine*, string) override {
        cout << "Processing transaction\n";
    }

    void insertMoney(VendingMachine*, int) override {
        cout << "Processing...\n";
    }

    void dispense(VendingMachine* vm) override {
        string name = vm->getSelectedProduct();
        Product p = vm->getInventory().getProduct(name);

        vm->getInventory().reduceStock(name);
        cout << "Dispensed: " << name << endl;

        int change = vm->getBalance() - p.getPrice();
        cout << "Returned change: " << change << endl;

        vm->resetBalance();
        vm->setState(vm->getIdleState());
    }

    void cancel(VendingMachine*) override {
        cout << "Cannot cancel now\n";
    }
};

// ===== Constructor & Destructor =====
VendingMachine::VendingMachine() {
    idleState = new IdleState();
    hasMoneyState = new HasMoneyState();
    dispenseState = new DispenseState();

    currentState = idleState;
    balance = 0;
}

VendingMachine::~VendingMachine() {
    delete idleState;
    delete hasMoneyState;
    delete dispenseState;
}

// ===== Main =====
int main() {
    VendingMachine vm;

    vm.getInventory().addProduct(Product("Coke", 50), 5);
    vm.getInventory().addProduct(Product("Pepsi", 40), 3);

    vm.selectProduct("Coke");
    vm.insertMoney(60);
    vm.dispense();

    return 0;
}