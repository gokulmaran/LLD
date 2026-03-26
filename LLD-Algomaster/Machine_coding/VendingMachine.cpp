#include <bits/stdc++.h>
using namespace std;

// ✅ Step 1: Requirements
// 1. Select product
// 2. Insert money
// 3. Dispense product
// 4. Return change / refund
// 5. Handle states (Idle, HasMoney, Dispensing)

// ✅ Step 2: Entities
// Entities:
//   - Product        → holds name, price
//   - Slot           → holds product, quantity
//   - VendingMachine → manages slots, balance, state
//   - State (interface) → defines machine behavior
//   - IdleState      → no money inserted
//   - HasMoneyState  → money inserted
//   - DispenseState  → dispensing product

// Responsibilities:
//   - Slot           → check availability, dispense product
//   - VendingMachine → manage state transitions, operations
//   - State          → define actions (select, insert, dispense)
//   - ConcreteStates → implement behavior based on current state

// ✅ Step 3: Class Design (Compressed)
// Product
// - name: string
// - price: double

// Slot
// - product: Product
// - quantity: int

// State (abstract)
// + selectProduct()
// + insertMoney()
// + dispense()
// + refund()

// IdleState / HasMoneyState / DispenseState111

// VendingMachine
// - slots: map<int, Slot*>
// - balance: double
// - selectedSlot: int
// - state: State*

// Functions:
// + setState()
// + selectProduct()
// + insertMoney()
// + dispense()
// + refund()

// ============================================================
// 🔹 Forward Declarations
// ============================================================

class VendingMachine;

// ============================================================
// 🔹 State Interface
// ============================================================

class State {
public:
    virtual void selectProduct(VendingMachine* vm, int slot) = 0;
    virtual void insertMoney(VendingMachine* vm, double amount) = 0;
    virtual void dispense(VendingMachine* vm) = 0;
    virtual void refund(VendingMachine* vm) = 0;
    virtual ~State() {}
};

// ============================================================
// 🔹 Product & Slot
// ============================================================

class Product {
public:
    string name;
    double price;

    Product(string n, double p) : name(n), price(p) {}
};

class Slot {
public:
    Product product;
    int quantity;

    Slot(Product p, int q) : product(p), quantity(q) {}

    bool isAvailable() {
        return quantity > 0;
    }

    void dispense() {
        if (quantity > 0) quantity--;
    }
};

// ============================================================
// 🔹 Vending Machine
// ============================================================

class IdleState;
class HasMoneyState;
class DispenseState;

class VendingMachine {
public:
    unordered_map<int, Slot*> slots;
    double balance = 0;
    int selectedSlot = -1;

    State* state;
    State* idleState;
    State* hasMoneyState;
    State* dispenseState;

    VendingMachine();

    void setState(State* s) {
        state = s;
    }

    void selectProduct(int slot) {
        state->selectProduct(this, slot);
    }

    void insertMoney(double amount) {
        state->insertMoney(this, amount);
    }

    void dispense() {
        state->dispense(this);
    }

    void refund() {
        state->refund(this);
    }
};

// ============================================================
// 🔹 Concrete States
// ============================================================

class IdleState : public State {
public:
    void selectProduct(VendingMachine* vm, int slot) override {
        if (vm->slots.find(slot) == vm->slots.end()) {
            cout << "Invalid slot\n";
            return;
        }
        vm->selectedSlot = slot;
        cout << "Product selected\n";
    }

    void insertMoney(VendingMachine* vm, double amount) override {
        vm->balance += amount;
        cout << "Money inserted: " << amount << endl;
        vm->setState(vm->hasMoneyState);
    }

    void dispense(VendingMachine* vm) override {
        cout << "Insert money first\n";
    }

    void refund(VendingMachine* vm) override {
        cout << "No money to refund\n";
    }
};

class HasMoneyState : public State {
public:
    void selectProduct(VendingMachine* vm, int slot) override {
        vm->selectedSlot = slot;
        cout << "Product re-selected\n";
    }

    void insertMoney(VendingMachine* vm, double amount) override {
        vm->balance += amount;
        cout << "Added more money\n";
    }

    void dispense(VendingMachine* vm) override {
        if (vm->selectedSlot == -1) {
            cout << "Select product first\n";
            return;
        }

        Slot* slot = vm->slots[vm->selectedSlot];

        if (!slot->isAvailable()) {
            cout << "Out of stock\n";
            return;
        }

        if (vm->balance < slot->product.price) {
            cout << "Insufficient balance\n";
            return;
        }

        vm->setState(vm->dispenseState);
        vm->dispense();
    }

    void refund(VendingMachine* vm) override {
        cout << "Refunded: " << vm->balance << endl;
        vm->balance = 0;
        vm->setState(vm->idleState);
    }
};

class DispenseState : public State {
public:
    void selectProduct(VendingMachine* vm, int slot) override {
        cout << "Wait, dispensing in progress\n";
    }

    void insertMoney(VendingMachine* vm, double amount) override {
        cout << "Wait, dispensing in progress\n";
    }

    void dispense(VendingMachine* vm) override {
        Slot* slot = vm->slots[vm->selectedSlot];

        slot->dispense();
        vm->balance -= slot->product.price;

        cout << "Dispensed: " << slot->product.name << endl;

        if (vm->balance > 0) {
            cout << "Returned change: " << vm->balance << endl;
            vm->balance = 0;
        }

        vm->selectedSlot = -1;
        vm->setState(vm->idleState);
    }

    void refund(VendingMachine* vm) override {
        cout << "Cannot refund during dispensing\n";
    }
};

// ============================================================
// 🔹 VendingMachine Constructor (after concrete states defined)
// ============================================================

VendingMachine::VendingMachine() {
    idleState     = new IdleState();
    hasMoneyState = new HasMoneyState();
    dispenseState = new DispenseState();
    state         = idleState;
}

// ============================================================
// 🔹 Driver
// ============================================================

int main() {
    VendingMachine vm;

    vm.slots[1] = new Slot(Product("Coke", 50), 5);
    vm.slots[2] = new Slot(Product("Pepsi", 40), 3);

    cout << "--- Normal Flow ---\n";
    vm.selectProduct(1);
    vm.insertMoney(100);
    vm.dispense();  // Dispenses Coke, returns change 50

    cout << "\n--- Refund Flow ---\n";
    vm.selectProduct(2);
    vm.insertMoney(40);
    vm.refund();    // Refunds 40

    cout << "\n--- Insufficient Balance ---\n";
    vm.selectProduct(1);
    vm.insertMoney(20);
    vm.dispense();  // Insufficient balance
    vm.refund();    // Refunds 20

    return 0;
}
