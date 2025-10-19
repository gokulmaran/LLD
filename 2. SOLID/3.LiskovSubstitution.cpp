#include <iostream>
using namespace std;

/*
Liskov Substitution Principle (LSP): Subclasses should be substitutable for their base classes without affecting the
correctness of the program. The Liskov Substitution Principle (LSP) states: Let
q(x) be a property provable about objects of x of type T. Then q(y) should be
provable for objects y of type S where S is a subtype of T. This means that
every subclass or derived class should be substitutable for their base or parent
class.
*/

// Shape interface equivalent (abstract base class)
class Shape {
public:
    virtual int getArea() = 0; // pure virtual function
    virtual ~Shape() {}        // virtual destructor
};

// Rectangle class implementing Shape
class Rectangle : public Shape {
private:
    int width;
    int height;

public:
    Rectangle(int width, int height) {
        this->width = width;
        this->height = height;
    }

    int getArea() {
        return width * height;
    }
};

// Square class implementing Shape
class Square : public Shape {
private:
    int side;

public:
    Square(int side) {
        this->side = side;
    }

    int getArea() {
        return side * side;
    }
};

// Main function to demonstrate
int main() {
    Rectangle rect(4, 5);
    Square square(4);

    cout << "Rectangle Area: " << rect.getArea() << endl; // 20
    cout << "Square Area: " << square.getArea() << endl;  // 16

    return 0;
}
