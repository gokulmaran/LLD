#include <iostream>
using namespace std;

//Hierarichal--one base class, multiple derived classes (Child1 and Child2).
// Base class
class Parent {
public:
    void show() {
        cout << "Parent class" << endl;
    }
};

// Derived class 1
class Child1 : public Parent {
public:
    void display() {
        cout << "Child1 class" << endl;
    }
};

// Derived class 2
class Child2 : public Parent {
public:
    void print() {
        cout << "Child2 class" << endl;
    }
};

int main() {
    // Create object of Parent
    Parent p;
    p.show();  // Output: Parent class

    // Create object of Child1
    Child1 c1;
    c1.show();    // Inherited from Parent
    c1.display(); // Output: Child1 class

    // Create object of Child2
    Child2 c2;
    c2.show();  // Inherited from Parent
    c2.print(); // Output: Child2 class

    return 0;
}
