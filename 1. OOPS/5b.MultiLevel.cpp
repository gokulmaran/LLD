#include <iostream>
using namespace std;

//one base class --derived class-->derived calss

// Base class (Grandparent)
class Grandparent {
public:
    void show() {
        cout << "Grandparent class" << endl;
    }
};

// Derived class (Parent) inherits from Grandparent
class Parent : public Grandparent {
public:
    void display() {
        cout << "Parent class" << endl;
    }
};

// Derived class (Child) inherits from Parent
class Child : public Parent {
public:
    void print() {
        cout << "Child class" << endl;
    }
};

int main() {
    // Create object of Grandparent
    Grandparent gp;
    gp.show();  // Output: Grandparent class

    // Create object of Parent
    Parent p;
    p.show();    // Inherited from Grandparent
    p.display(); // Output: Parent class

    // Create object of Child
    Child c;
    c.show();     // Inherited from Grandparent
    c.display();  // Inherited from Parent
    c.print();    // Output: Child class

    return 0;
}
