#include <iostream>
using namespace std;

/*
 State interface --> Concrete states --> Context
*/

class Order; // forward declare ONLY class name, not methods (allowed)


// ---- State Interface ----
class OrderStates {
public:
    virtual string name() = 0;
    virtual void proceed(Order* order) = 0;
    virtual ~OrderStates() {}
};


// ---- Context ----
class Order {
public:
    OrderStates* state;

    Order(OrderStates* s) : state(s) {}

    void setState(OrderStates* s) {
        delete state;     // free old state
        state = s;
    }

    void next() {
        state->proceed(this);
    }

    void show() {
        cout << "Current State: " << state->name() << endl;
    }

    ~Order() {
        delete state;
    }
};


// ---- Concrete States ----
class Placed : public OrderStates {
public:
    string name() {
        return "Placed";
    }
    void proceed(Order* order);
};

class Shipped : public OrderStates {
public:
    string name() {
        return "Shipped";
    }
    void proceed(Order* order);
};

class Delivered : public OrderStates {
public:
    string name() {
        return "Delivered";
    }
    void proceed(Order* order) {
        cout << "Order already delivered. No further transitions.\n";
    }
};


// ---- Proceed Implementations (after all classes exist) ----

void Placed::proceed(Order* order) {
    order->setState(new Shipped());
}

void Shipped::proceed(Order* order) {
    order->setState(new Delivered());
}


// ---- Main ----
int main() {
    Order order(new Placed());

    order.show();
    order.next();

    order.show();
    order.next();

    order.show();
    order.next(); // calling again on Delivered

    return 0;
}
