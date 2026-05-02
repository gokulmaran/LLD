#include <bits/stdc++.h>
using namespace std;

class Keyboard {
public:
    virtual void type() = 0;
};

class WiredKeyboard : public Keyboard {
public:
    void type() override {
        cout << "Typing with wired keyboard\n";
    }
};

class BluetoothKeyboard : public Keyboard {
public:
    void type() override {
        cout << "Typing with bluetooth keyboard\n";
    }
};

class Computer {
private:
    Keyboard* keyboard;

public:
    Computer(Keyboard* k) {
        keyboard = k;
    }

    void use() {
        keyboard->type();
    }
};

int main() {
    WiredKeyboard wk;
    Computer c(&wk);

    c.use();
}