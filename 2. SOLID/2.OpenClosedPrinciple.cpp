#include <iostream>
#include <cmath>
using namespace std;

/*
Open-Closed Principle (OCP) Definition: Software entities (classes, modules,
functions, etc.) should be open for extension but closed for modification. Benefits: Encourages the addition of new features without altering existing code.
Enhances stability and reduces the risk of introducing bugs
*/

// Interface equivalent (abstract base class)
class Shape {
public:
    virtual double area() = 0; // pure virtual function
    virtual ~Shape() {}        // virtual destructor
};

// Rectangle class implementing Shape
class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double length, double width) {
        this->length = length;
        this->width = width;
    }

    double area() {
        return length * width;
    }
};

// Circle class implementing Shape
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double radius) {
        this->radius = radius;
    }

    double area() {
        return M_PI * radius * radius;
    }
};

// AreaCalculator class
class AreaCalculator {
public:
    double calculateArea(Shape& shape) {
        return shape.area();
    }
};

// Main function to demonstrate
int main() {
    Rectangle rect(5.0, 3.0);
    Circle circle(4.0);

    AreaCalculator calc;

    cout << "Rectangle Area: " << calc.calculateArea(rect) << endl;
    cout << "Circle Area: " << calc.calculateArea(circle) << endl;

    return 0;
}
