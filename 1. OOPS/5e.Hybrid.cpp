#include <iostream>
using namespace std;

//one,two base class,-->derived class (it has access of all classes)
// Base class
class Grandparent {
public:
    void showGrandparent() {
        cout << "Grandparent class" << endl;
    }
};

// First parent class inherits from Grandparent (multilevel)
class Parent1 : public Grandparent {
public:
    void showParent1() {
        cout << "Parent1 class" << endl;
    }
};

// Second parent class (separate)
class Parent2 {
public:
    void showParent2() {
        cout << "Parent2 class" << endl;
    }
};

// Child class inherits from both Parent1 and Parent2 (multiple inheritance)
class Child : public Parent1, public Parent2 {
public:
    void showChild() {
        cout << "Child class" << endl;
    }
};

int main() {
    Child c;

    // Access methods from all ancestors
    c.showGrandparent(); // from Grandparent (via Parent1)
    c.showParent1();     // from Parent1
    c.showParent2();     // from Parent2
    c.showChild();       // from Child itself

    return 0;
}
