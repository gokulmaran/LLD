/*
             ┌──────────────────┐
             │   Color (Implementor) │
             │ + applyColor()        │
             └────────▲───────────┘
                      │
      ┌──────────────────────────────┐
      │                              │
┌──────────────┐             ┌──────────────┐
│ RedColor     │             │ BlueColor    │
│ + applyColor()│            │ + applyColor()│
└──────────────┘             └──────────────┘

             ┌─────────────────────┐
             │ Shape (Abstraction) │
             │ + drawShape()       │
             │ - color: Color*     │
             └────────▲────────────┘
                      │
      ┌──────────────────────────────┐
      │                              │
┌──────────────┐             ┌──────────────┐
│ Circle       │             │ Square       │
│ + drawShape()│             │ + drawShape()│
└──────────────┘             └──────────────┘
*/
//Decouples abstraction from implementation
#include <iostream>
using namespace std;

// Implementor
class Color {
public:
    virtual void applyColor() = 0;
    virtual ~Color() = default;
};

// Concrete Implementors
class RedColor : public Color {
public:
    void applyColor() override {
        cout << "Red Color";
    }
};

class BlueColor : public Color {
public:
    void applyColor() override {
        cout << "Blue Color";
    }
};

// Abstraction
class Shape {
protected:
    Color* color; // Bridge connection
public:
    Shape(Color* c) : color(c) {}
    virtual void drawShape() = 0;
    virtual ~Shape() = default;
};

// Refined Abstractions
class Circle : public Shape {
public:
    Circle(Color* c) : Shape(c) {}
    void drawShape() override {
        cout << "Drawing Circle with ";
        color->applyColor();
        cout << endl;
    }
};

class Square : public Shape {
public:
    Square(Color* c) : Shape(c) {}
    void drawShape() override {
        cout << "Drawing Square with ";
        color->applyColor();
        cout << endl;
    }
};

// Client
int main() {
    Color* red = new RedColor();
    Color* blue = new BlueColor();

    Shape* circle = new Circle(red);
    Shape* square = new Square(blue);

    circle->drawShape();
    square->drawShape();

    delete circle;
    delete square;
    delete red;
    delete blue;
    return 0;
}
