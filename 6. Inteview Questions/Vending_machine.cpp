#include <iostream>
#include <unordered_map>
using namespace std;

/* =======================
   Forward Declarations
   ======================= */
class VendingMachine;
class NoCoinState;
class HasCoinState;
class DispenseState;

/* =======================
   State Interface
   ======================= */
class State {
public:
    virtual void insertCoin(VendingMachine* vm) = 0;
    virtual void selectItem(VendingMachine* vm, int code) = 0;
    virtual void dispense(VendingMachine* vm) = 0;
    virtual ~State() = default;
};

/* =======================
   Context (INLINE DEFINITION)
   ======================= */
class VendingMachine {
private:
    State* currentState;
    unordered_map<int, string> items;

public:
    // Constructor
    VendingMachine(State* state) : currentState(state) {
        items[1] = "Coke";
        items[2] = "Pepsi";
        items[3] = "Water";
    }

    // State transition
    void setState(State* state) {
        delete currentState;
        currentState = state;
    }

    bool hasItem(int code) {
        return items.find(code) != items.end();
    }

    string getItem(int code) {
        return items.at(code);
    }

    void insertCoin() {
        currentState->insertCoin(this);
    }

    void selectItem(int code) {
        currentState->selectItem(this, code);
    }

    void dispense() {
        currentState->dispense(this);
    }

    ~VendingMachine() {
        delete currentState;
    }
};

/* =======================
   Concrete States (DECLARE)
   ======================= */
class NoCoinState : public State {
public:
    void insertCoin(VendingMachine* vm) override;
    void selectItem(VendingMachine* vm, int code) override;
    void dispense(VendingMachine* vm) override;
};

class HasCoinState : public State {
public:
    void insertCoin(VendingMachine* vm) override;
    void selectItem(VendingMachine* vm, int code) override;
    void dispense(VendingMachine* vm) override;
};

class DispenseState : public State {
private:
    int itemCode;

public:
    explicit DispenseState(int code);
    void insertCoin(VendingMachine* vm) override;
    void selectItem(VendingMachine* vm, int code) override;
    void dispense(VendingMachine* vm) override;
};

/* =======================
   Concrete States (DEFINE)
   ======================= */

// NoCoinState
void NoCoinState::insertCoin(VendingMachine* vm) {
    cout << "Coin inserted\n";
    vm->setState(new HasCoinState());
}

void NoCoinState::selectItem(VendingMachine*, int) {
    cout << "Insert coin first\n";
}

void NoCoinState::dispense(VendingMachine*) {
    cout << "No coin inserted\n";
}

// HasCoinState
void HasCoinState::insertCoin(VendingMachine*) {
    cout << "Coin already inserted\n";
}

void HasCoinState::selectItem(VendingMachine* vm, int code) {
    if (vm->hasItem(code)) {
        cout << "Item selected\n";
        vm->setState(new DispenseState(code));
    } else {
        cout << "Invalid item code\n";
    }
}

void HasCoinState::dispense(VendingMachine*) {
    cout << "Select item first\n";
}

// DispenseState
DispenseState::DispenseState(int code) : itemCode(code) {}

void DispenseState::insertCoin(VendingMachine*) {
    cout << "Please wait, dispensing item\n";
}

void DispenseState::selectItem(VendingMachine*, int) {
    cout << "Already selected\n";
}

void DispenseState::dispense(VendingMachine* vm) {
    cout << "Dispensing: " << vm->getItem(itemCode) << endl;
    vm->setState(new NoCoinState());
}

/* =======================
   Client
   ======================= */
int main() {
    VendingMachine vm(new NoCoinState());

    vm.selectItem(1);   // Insert coin first
    vm.insertCoin();    // Coin inserted
    vm.selectItem(1);   // Item selected
    vm.dispense();      // Dispensing Coke

    return 0;
}
