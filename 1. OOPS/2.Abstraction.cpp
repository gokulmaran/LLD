#include <iostream>
using namespace std;
/*Abstraction: Abstraction involves highlighting essential features of an
object while hiding unnecessary details. It helps simplify complex systems by focusing
on relevant aspects and ignoring implementation complexities.

Example:
In a banking application, users interact with an ATM to perform transactions
without needing to know the internal workings of the ATM. Importance: Abstraction
simplifies complex systems by focusing on what an object does rather
than how it does it. This helps in managing complexity and improving code
readability. 

Implementation: Abstract classes and interfaces define common
methods and properties but leave the specifics to derived classes.*/

// Abstract class
class Shape {
public:
    // Pure virtual function (abstract method)
    virtual void draw() = 0;  
};

// Derived class: Circle
class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing Circle" << endl;
    }
};

// Derived class: Rectangle
class Rectangle : public Shape {
public:
    void draw() override {
        cout << "Drawing Rectangle" << endl;
    }
};

// Main function
int main() {
    Circle c;
    Rectangle r;

    c.draw();
    r.draw();

    // Or using base class pointer (polymorphism)
    Shape* shape1 = &c;
    Shape* shape2 = &r;

    shape1->draw();
    shape2->draw();

    return 0;
}
