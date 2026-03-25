#include <bits/stdc++.h>
using namespace std;

/*Programmatic Example
Translating the door example above. First of all we have our Door interface
and some implementation for it*/
/* =======================
   Abstract Products
   ======================= */

class Door {
public:
    virtual void getDescription() = 0;
    virtual ~Door() = default;
};

class DoorFittingExpert {
public:
    virtual void getDescription() = 0;
    virtual ~DoorFittingExpert() = default;
};

/* =======================
   Concrete Products
   ======================= */
// Pizza Meal
class WoodenDoor : public Door {
public:
    void getDescription() override {
        cout << "I am a wooden door\n";
    }
};

class IronDoor : public Door {
public:
    void getDescription() override {
        cout << "I am an iron door\n";
    }
};

class Carpenter : public DoorFittingExpert {
public:
    void getDescription() override {
        cout << "I can only fit wooden doors\n";
    }
};

class Welder : public DoorFittingExpert {
public:
    void getDescription() override {
        cout << "I can only fit iron doors\n";
    }
};
/*Now we have our abstract factory that would let us make family of related
objects i.e. wooden door factory would create a wooden door and wooden door
fitting expert and iron door factory would create an iron door and iron door fitting
expert.*/
/* =======================
   Abstract Factory
   ======================= */
class DoorFactory {
public:
    virtual Door* makeDoor() = 0;
    virtual DoorFittingExpert* makeFittingExpert() = 0;
    virtual ~DoorFactory() {}
};

/* =======================
   Concrete Factories
   ======================= */
class WoodenDoorFactory : public DoorFactory {
public:
    Door* makeDoor() override {
        return new WoodenDoor();
    }

    DoorFittingExpert* makeFittingExpert() override {
        return new Carpenter();
    }
};

class IronDoorFactory : public DoorFactory {
public:
    Door* makeDoor() override {
        return new IronDoor();
    }

    DoorFittingExpert* makeFittingExpert() override {
        return new Welder();
    }
};


//And then it can be used as
int main() {
    DoorFactory* woodenFactory = new WoodenDoorFactory();

    Door* door = woodenFactory->makeDoor();
    DoorFittingExpert* expert = woodenFactory->makeFittingExpert();

    door->getDescription();
    expert->getDescription();

    // cleanup
    delete door;
    delete expert;
    delete woodenFactory;

    cout << "----\n";

    DoorFactory* ironFactory = new IronDoorFactory();

    door = ironFactory->makeDoor();
    expert = ironFactory->makeFittingExpert();

    door->getDescription();
    expert->getDescription();

    // cleanup
    delete door;
    delete expert;
    delete ironFactory;

    return 0;
}
