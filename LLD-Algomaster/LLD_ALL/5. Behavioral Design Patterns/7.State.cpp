#include <iostream>
using namespace std;
/*
+------------------+
|     Product      |
+------------------+
| - state:         |
|   ProductState   |
+------------------+
| + setCurrentState|
+------------------+
          |
          | has-a
          v
+------------------------+
|     ProductState      |
+------------------------+
| + operation1(Product)|
| + operation2(Product)|
| + operationN(Product)|
+------------------------+
     ^           ^           ^
     | is-a      | is-a      | is-a
+---------+  +---------+  +---------+
| State 1 |  | State 2 |  | State 3 |
+---------+  +---------+  +---------+
*/
/* =======================
   Forward Declarations
   ======================= */
class TrafficLight;


/* =======================
   State Interface
   ======================= */
class TrafficLightState {
public:
    virtual void action(TrafficLight* signal) = 0;
    virtual ~TrafficLightState() = default;
};

/* =======================
   Context
   ======================= */
class TrafficLight {
private:
    TrafficLightState* state;

public:
    TrafficLight(TrafficLightState* initialState) : state(initialState) {}

    void setState(TrafficLightState* newState) {
        delete state;
        state = newState;
    }

    void change() {
        state->action(this);
    }

    ~TrafficLight() {
        delete state;
    }
};

/* =======================
   Concrete States (DECLARATION)
   ======================= */
class RedState : public TrafficLightState {
public:
    void action(TrafficLight* signal) override;
};

class GreenState : public TrafficLightState {
public:
    void action(TrafficLight* signal) override;
};

class YellowState : public TrafficLightState {
public:
    void action(TrafficLight* signal) override;
};

/* =======================
   Concrete States (DEFINITION)
   ======================= */
void RedState::action(TrafficLight* signal) {
    cout << "RED → STOP\n";
    signal->setState(new GreenState());
}

void GreenState::action(TrafficLight* signal) {
    cout << "GREEN → GO\n";
    signal->setState(new YellowState());
}

void YellowState::action(TrafficLight* signal) {
    cout << "YELLOW → SLOW DOWN\n";
    signal->setState(new RedState());
}

/* =======================
   Client
   ======================= */
int main() {
    TrafficLight trafficLight(new RedState());

    trafficLight.change(); // RED → GREEN
    trafficLight.change(); // GREEN → YELLOW
    trafficLight.change(); // YELLOW → RED

    return 0;
}
