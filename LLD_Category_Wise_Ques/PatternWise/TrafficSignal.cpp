#include <iostream>

class TrafficLight;

// 1. State Interface
class TrafficLightState {
public:
    virtual ~TrafficLightState() {}
    virtual void handle(TrafficLight* context) = 0;
};

// 2. Context Class
class TrafficLight {
private:
    TrafficLightState* currentState;

public:
    TrafficLight(TrafficLightState* initialState) : currentState(initialState) {}

    // Manual memory management for LLD demonstration
    void setState(TrafficLightState* newState) {
        if (currentState) delete currentState; 
        currentState = newState;
    }

    void change() {
        currentState->handle(this);
    }
};


//3. Concrete states
class RedState : public TrafficLightState {
public:
    void handle(TrafficLight* context) override;
};

class GreenState : public TrafficLightState {
public:
    void handle(TrafficLight* context) override;
};

class YellowState : public TrafficLightState {
public:
    void handle(TrafficLight* context) override;
};

// Logic Implementations
void RedState::handle(TrafficLight* context) {
    std::cout << "[RED] Stop! Changing to Green...\n";
    context->setState(new GreenState());
}

void GreenState::handle(TrafficLight* context) {
    std::cout << "[GREEN] Go! Changing to Yellow...\n";
    context->setState(new YellowState());
}

void YellowState::handle(TrafficLight* context) {
    std::cout << "[YELLOW] Caution! Changing to Red...\n";
    context->setState(new RedState());
}

int main() {
    // Initialize with Red
    TrafficLight* light = new TrafficLight(new RedState());

    // Manually trigger 3 cycles
    for (int i = 0; i < 3; i++) {
        light->change();
    }

    delete light;
    return 0;
}
