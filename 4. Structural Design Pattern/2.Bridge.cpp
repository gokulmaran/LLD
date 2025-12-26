#include <iostream>
using namespace std;

/* =======================
   Step 1: Implementor
   ======================= */
class BreathingProcess {
public:
    virtual void breathe() = 0;
    virtual ~BreathingProcess() = default;
};

/* =======================
   Step 2: Concrete Implementors
   ======================= */
class GillBreathing : public BreathingProcess {
public:
    void breathe() override {
        cout << "Breathing through gills." << endl;
    }
};

class LungBreathing : public BreathingProcess {
public:
    void breathe() override {
        cout << "Breathing through lungs." << endl;
    }
};

class Photosynthesis : public BreathingProcess {
public:
    void breathe() override {
        cout << "Breathing through process of photosynthesis. "
             << "Releases Oxygen through leaves." << endl;
    }
};

/* =======================
   Step 3: Abstraction
   ======================= */
class LivingThings {
protected:
    BreathingProcess* breathingProcess;

public:
    LivingThings(BreathingProcess* bp) : breathingProcess(bp) {}
    virtual void breathe() = 0;
    virtual ~LivingThings() = default;
};

/* =======================
   Step 4: Refined Abstractions
   ======================= */
class Dog : public LivingThings {
public:
    Dog(BreathingProcess* bp) : LivingThings(bp) {}

    void breathe() override {
        cout << "Dog: ";
        breathingProcess->breathe();
    }
};

class Fish : public LivingThings {
public:
    Fish(BreathingProcess* bp) : LivingThings(bp) {}

    void breathe() override {
        cout << "Fish: ";
        breathingProcess->breathe();
    }
};

class Tree : public LivingThings {
public:
    Tree(BreathingProcess* bp) : LivingThings(bp) {}

    void breathe() override {
        cout << "Tree: ";
        breathingProcess->breathe();
    }
};

/* =======================
   Client Code
   ======================= */
int main() {
    BreathingProcess* lungBreathing = new LungBreathing();
    BreathingProcess* gillBreathing = new GillBreathing();
    BreathingProcess* photosynthesis = new Photosynthesis();

    LivingThings* dog = new Dog(lungBreathing);
    LivingThings* fish = new Fish(gillBreathing);
    LivingThings* tree = new Tree(photosynthesis);

    dog->breathe();
    fish->breathe();
    tree->breathe();

    // Cleanup
    delete dog;
    delete fish;
    delete tree;

    delete lungBreathing;
    delete gillBreathing;
    delete photosynthesis;

    return 0;
}
