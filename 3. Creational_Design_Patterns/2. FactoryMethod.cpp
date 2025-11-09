/* 
          ┌───────────────────┐
          │    Creator        │  <--- Factory
          ├───────────────────┤
          │ + factoryMethod() │
          └───────────────────┘
          ┌───────────────────┐
          │     Product       │  <--- Interface
          └───────────────────┘
                    ▲
        ┌───────────┴────────────┐
        │                         │
 ┌──────────────┐         ┌──────────────┐
 │ ConcreteProdA│         │ ConcreteProdB│
 └──────────────┘         └──────────────┘
*/

#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    void draw() override { cout << "Drawing Circle\n"; }
};

class Square : public Shape {
public:
    void draw() override { cout << "Drawing Square\n"; }
};

class ShapeFactory {
public:
    static Shape* getShape(string type) {
        if (type == "circle") return new Circle();
        else if (type == "square") return new Square();
        return nullptr;
    }
};

int main() {
    Shape* s1 = ShapeFactory::getShape("circle");
    Shape* s2 = ShapeFactory::getShape("square");
    s1->draw();
    s2->draw();
}
