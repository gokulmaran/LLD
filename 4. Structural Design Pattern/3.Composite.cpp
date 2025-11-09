/*
                 ┌──────────────────┐
                 │   Shape           │  ← Abstract Component
                 │ + draw()          │
                 └─────────▲────────┘
                           │
       ┌───────────────────┴────────────────────┐
       │                                        │
┌──────────────┐                     ┌────────────────────┐
│   Circle     │                     │  CompositeShape    │
│ + draw()     │                     │ + add(Shape*)      │
└──────────────┘                     │ + remove(Shape*)   │
                                     │ + draw()           │
                                     └────────────────────┘
*/
//The Composite Pattern lets you treat individual objects and groups of objects uniformly.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Component
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

// Leaf 1
class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing Circle\n";
    }
};

// Leaf 2
class Square : public Shape {
public:
    void draw() override {
        cout << "Drawing Square\n";
    }
};

// Composite
class CompositeShape : public Shape {
    vector<Shape*> shapes;  // stores children
public:
    void add(Shape* s) {
        shapes.push_back(s);
    }

    void remove(Shape* s) {  // or rename to removeShape()
        shapes.erase(std::remove(shapes.begin(), shapes.end(), s), shapes.end());
    }

    void draw() override {
        cout << "Drawing Composite Shape containing:\n";
        for (auto shape : shapes)
            shape->draw();
    }

    ~CompositeShape() {
        for (auto s : shapes)
            delete s;
    }
};

// Client
int main() {
    Shape* circle = new Circle();
    Shape* square = new Square();

    CompositeShape* group = new CompositeShape();
    group->add(circle);
    group->add(square);

    group->draw();

    delete group;
    return 0;
}
