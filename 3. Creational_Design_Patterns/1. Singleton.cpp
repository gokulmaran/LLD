/*
        ┌────────────────────────┐
        │       Singleton        │
        ├────────────────────────┤
        │ - instance : Singleton*│
        ├────────────────────────┤
        │ - Singleton()          │
        │ + getInstance() : Singleton* │
        │ + showMessage() : void │
        └────────────────────────┘
*/

#include <iostream>
using namespace std;

class Singleton {
private:
    static Singleton* instance;
    Singleton() { cout << "Instance created\n"; }
public:
    static Singleton* getInstance() {
        if (instance == nullptr)
            instance = new Singleton();
        return instance;
    }
    void showMessage() { cout << "Hello from Singleton!\n"; }
};

Singleton* Singleton::instance = nullptr;

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
    s1->showMessage();
    cout << (s1 == s2 ? "Same instance\n" : "Different instances\n");
}
