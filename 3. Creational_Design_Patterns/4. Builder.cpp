/*
```
┌─────────────────┐          ┌──────────────────┐          ┌─────────────────┐
│      Pizza      │          │  PizzaBuilder    │          │  PizzaDirector   │
├─────────────────┤          ├──────────────────┤          ├─────────────────┤
│ - dough: string │<>------->│ + setDough()     │          │ + makeHawaiian   │
│ - sauce: string │          │   (string): void │          │   Pizza()        │
│ - topping:      │          │ + setSauce()     │          │   (builder:      │
│   string        │          │   (string): void │          │    PizzaBuilder │
│ + display():    │          │ + setTopping()   │          │   ): void        │
│   void          │          │   (string): void │          └─────────────────┘
└─────────────────┘          │ + getPizza():    │
                             │   Pizza          │
                             └──────────────────┘
                                      ^
                                      |
                             ┌──────────────────┐
                             │HawaiianPizza     │
                             │Builder           │
                             ├──────────────────┤
                             │ - pizza:         │
                             │   Pizza          │
                             ├──────────────────┤
                             │ + setDough()     │
                             │   (string): void │
                             │ + setSauce()     │
                             │   (string): void │
                             │ + setTopping()   │
                             │   (string): void │
                             │ + getPizza():    │
                             │   Pizza          │
                             └──────────────────┘
```
*/
#include <iostream>
#include <string>
#include <vector>

// Product class: Represents the complex object being built
class Pizza {
public:
    std::string dough;
    std::string sauce;
    std::string topping;

    void display() const {
        std::cout << "Pizza with:\n";
        std::cout << "Dough: " << dough << "\n";
        std::cout << "Sauce: " << sauce << "\n";
        std::cout << "Topping: " << topping << "\n";
    }
};

// Abstract Builder interface
class PizzaBuilder {
public:
    virtual ~PizzaBuilder() = default;
    virtual void setDough(const std::string& dough) = 0;
    virtual void setSauce(const std::string& sauce) = 0;
    virtual void setTopping(const std::string& topping) = 0;
    virtual Pizza getPizza() = 0;
};

// Concrete Builder
class HawaiianPizzaBuilder : public PizzaBuilder {
private:
    Pizza pizza;

public:
    void setDough(const std::string& dough) override {
        pizza.dough = dough;
    }

    void setSauce(const std::string& sauce) override {
        pizza.sauce = sauce;
    }

    void setTopping(const std::string& topping) override {
        pizza.topping = topping;
    }

    Pizza getPizza() override {
        return pizza;
    }
};

// Director: Orchestrates the building process
class PizzaDirector {
public:
    void makeHawaiianPizza(PizzaBuilder& builder) {
        builder.setDough("cross");
        builder.setSauce("mild");
        builder.setTopping("ham+pineapple");
    }
};

int main() {
    PizzaDirector director;
    HawaiianPizzaBuilder builder;

    director.makeHawaiianPizza(builder);
    Pizza pizza = builder.getPizza();

    pizza.display();
    return 0;
}