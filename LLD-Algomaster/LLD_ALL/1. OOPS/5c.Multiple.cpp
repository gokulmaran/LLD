#include <iostream>
using namespace std;

// multiple 2 base class -one derived class
// Base class 1
class Parent1 {
public:
    void show1() {
        cout << "Parent1 class" << endl;
    }
};

// Base class 2
class Parent2 {
public:
    void show2() {
        cout << "Parent2 class" << endl;
    }
};

// Derived class inheriting from both Parent1 and Parent2
class Child : public Parent1, public Parent2 {
public:
    void display() {
        cout << "Child class" << endl;
    }
};

int main() {
    Child c;

    // Access methods from both base classes
    c.show1();   // Output: Parent1 class
    c.show2();   // Output: Parent2 class
    c.display(); // Output: Child class

    return 0;
}
