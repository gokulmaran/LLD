/*        ┌────────────────────────┐
          │   AbstractFactory      │
          ├────────────────────────┤
          │ + createShape()        │
          │ + createColor()        │
          └────────────────────────┘
                 ▲                ▲
     ┌────────────┘                └────────────┐
┌──────────────┐                   ┌──────────────┐
│ ShapeFactory │                   │ ColorFactory │
└──────────────┘                   └──────────────┘
*/

#include <iostream>
using namespace std;

class Shape { 
    public: virtual void draw() = 0; 
};
class Circle : public Shape { 
    public: void draw() override { 
        cout << "Circle\n"; 
    }
 };
class Square : public Shape { public: void draw() override { cout << "Square\n"; } };

class Color { public: virtual void fill() = 0; };

class Red : public Color { public: void fill() override { cout << "Red\n"; } };
class Blue : public Color { public: void fill() override { cout << "Blue\n"; } };

class AbstractFactory {
public:
    virtual Shape* getShape(string type) { return nullptr; }
    virtual Color* getColor(string type) { return nullptr; }
};

class ShapeFactory : public AbstractFactory {
public:
    Shape* getShape(string type) override {
        if (type == "circle") return new Circle();
        if (type == "square") return new Square();
        return nullptr;
    }
};

class ColorFactory : public AbstractFactory {
public:
    Color* getColor(string type) override {
        if (type == "red") return new Red();
        if (type == "blue") return new Blue();
        return nullptr;
    }
};

class FactoryProducer {
public:
    static AbstractFactory* getFactory(string type) {
        if (type == "shape") return new ShapeFactory();
        if (type == "color") return new ColorFactory();
        return nullptr;
    }
};

int main() {
    AbstractFactory* shapeFactory = FactoryProducer::getFactory("shape");
    Shape* s1 = shapeFactory->getShape("circle");
    s1->draw();

    AbstractFactory* colorFactory = FactoryProducer::getFactory("color");
    Color* c1 = colorFactory->getColor("red");
    c1->fill();
}
