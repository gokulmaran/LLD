#include <iostream>
using namespace std;

/* =========================
   Receiver
   ========================= */
class Light {
public:
    void turnOn() {
        cout << "Light is ON\n";
    }

    void turnOff() {
        cout << "Light is OFF\n";
    }
};

/* =========================
   Command Interface
   ========================= */
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

/* =========================
   Concrete Commands
   ========================= */
class LightOnCommand : public Command {
private:
    Light* light;

public:
    LightOnCommand(Light* l) : light(l) {}

    void execute() override {
        light->turnOn();
    }
};

class LightOffCommand : public Command {
private:
    Light* light;

public:
    LightOffCommand(Light* l) : light(l) {}

    void execute() override {
        light->turnOff();
    }
};

/* =========================
   Invoker
   ========================= */
class RemoteControl {
private:
    Command* command;

public:
    void setCommand(Command* cmd) {
        command = cmd;
    }

    void pressButton() {
        command->execute();
    }
};

/* =========================
   Client
   ========================= */
int main() {
    cout << "===== Simple Command Pattern Demo =====\n\n";

    Light livingRoomLight;
    RemoteControl remote;

    // Turn ON light
    remote.setCommand(new LightOnCommand(&livingRoomLight));
    remote.pressButton();

    // Turn OFF light
    remote.setCommand(new LightOffCommand(&livingRoomLight));
    remote.pressButton();

    return 0;
}
