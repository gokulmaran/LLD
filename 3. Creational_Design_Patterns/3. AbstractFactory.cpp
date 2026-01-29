#include <iostream>
using namespace std;

/* =======================
   Abstract Products
   ======================= */
class MainItem {
public:
    virtual void prepare() = 0;
    virtual ~MainItem() {}
};

class SideItem {
public:
    virtual void prepare() = 0;
    virtual ~SideItem() {}
};

/* =======================
   Concrete Products
   ======================= */
// Pizza Meal
class Pizza : public MainItem {
public:
    void prepare() override {
        cout << "Preparing Pizza" << endl;
    }
};

class GarlicBread : public SideItem {
public:
    void prepare() override {
        cout << "Preparing Garlic Bread" << endl;
    }
};

// Burger Meal
class Burger : public MainItem {
public:
    void prepare() override {
        cout << "Preparing Burger" << endl;
    }
};

class Fries : public SideItem {
public:
    void prepare() override {
        cout << "Preparing Fries" << endl;
    }
};

/* =======================
   Abstract Factory
   ======================= */
class MealFactory {
public:
    virtual MainItem* createMainItem() = 0;
    virtual SideItem* createSideItem() = 0;
    virtual ~MealFactory() {}
};

/* =======================
   Concrete Factories
   ======================= */
class PizzaMealFactory : public MealFactory {
public:
    MainItem* createMainItem() override {
        return new Pizza();
    }

    SideItem* createSideItem() override {
        return new GarlicBread();
    }
};

class BurgerMealFactory : public MealFactory {
public:
    MainItem* createMainItem() override {
        return new Burger();
    }

    SideItem* createSideItem() override {
        return new Fries();
    }
};

/* =======================
   Client
   ======================= */
class Restaurant {
private:
    MealFactory* factory;

public:
    Restaurant(MealFactory* f) : factory(f) {}

    void orderMeal() {
        MainItem* mainItem = factory->createMainItem();
        SideItem* sideItem = factory->createSideItem();

        mainItem->prepare();
        sideItem->prepare();

        delete mainItem;
        delete sideItem;
    }
};

/* =======================
   Main
   ======================= */
int main() {
    MealFactory* pizzaFactory = new PizzaMealFactory();
    Restaurant pizzaRestaurant(pizzaFactory);
    pizzaRestaurant.orderMeal();

    cout << "----------------" << endl;

    MealFactory* burgerFactory = new BurgerMealFactory();
    Restaurant burgerRestaurant(burgerFactory);
    burgerRestaurant.orderMeal();

    delete pizzaFactory;
    delete burgerFactory;

    return 0;
}
