#include <iostream>
using namespace std;
//single one base calss,one derived class

// Base class (Parent)
class Parent {
public:
    void show() {
        cout << "This is the parent class" << endl;
    }
};

// Derived class (Child) inherits from Parent
class Child : public Parent {
public:
    void display() {
        cout << "This is the child class" << endl;
    }
};

int main() {
    // Create object of Parent
    Parent p;
    p.show();  // Output: This is the parent class

    // Create object of Child
    Child c;
    c.show();     // Child inherits this method from Parent
    c.display();  // Output: This is the child class

    return 0;
}
