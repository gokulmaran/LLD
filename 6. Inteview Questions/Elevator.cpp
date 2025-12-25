#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>

using namespace std;

/* ===================== ENUMS ===================== */

enum class Direction {
    UP,
    DOWN,
    IDLE
};

enum class DoorState {
    OPEN,
    CLOSED
};

/* ===================== DOOR ===================== */

class Door {
    DoorState state = DoorState::CLOSED;

public:
    void open() {
        state = DoorState::OPEN;
        cout << "Door opened\n";
    }

    void close() {
        state = DoorState::CLOSED;
        cout << "Door closed\n";
    }
};

/* ===================== ELEVATOR CAR ===================== */

class ElevatorCar {
public:
    int id;
    int currentFloor;
    Direction direction;
    Door door;
    queue<int> requests;

    ElevatorCar(int id)
        : id(id), currentFloor(0), direction(Direction::IDLE) {}

    void addRequest(int floor) {
        requests.push(floor);
    }

    void move() {
        if (requests.empty()) {
            direction = Direction::IDLE;
            return;
        }

        int target = requests.front();
        requests.pop();

        direction = (target > currentFloor)
                        ? Direction::UP
                        : Direction::DOWN;

        cout << "Elevator " << id
             << " moving from " << currentFloor
             << " to " << target << endl;

        currentFloor = target;
        door.open();
        door.close();
    }
};

/* ===================== STRATEGY ===================== */

class ElevatorSelectionStrategy {
public:
    virtual ElevatorCar* selectElevator(
        vector<ElevatorCar*>& elevators,
        int floor,
        Direction dir) = 0;

    virtual ~ElevatorSelectionStrategy() = default;
};

/* ===================== NEAREST STRATEGY ===================== */

class NearestElevatorStrategy : public ElevatorSelectionStrategy {
public:
    ElevatorCar* selectElevator(
        vector<ElevatorCar*>& elevators,
        int floor,
        Direction) override {

        ElevatorCar* best = nullptr;
        int minDist = INT_MAX;

        for (auto e : elevators) {
            int dist = abs(e->currentFloor - floor);
            if (dist < minDist) {
                minDist = dist;
                best = e;
            }
        }
        return best;
    }
};

/* ===================== CONTROLLER ===================== */

class ElevatorController {
    vector<ElevatorCar*> elevators;
    ElevatorSelectionStrategy* strategy;

public:
    ElevatorController(ElevatorSelectionStrategy* strategy)
        : strategy(strategy) {}

    void addElevator(ElevatorCar* e) {
        elevators.push_back(e);
    }

    void requestElevator(int floor, Direction dir) {
        ElevatorCar* e =
            strategy->selectElevator(elevators, floor, dir);
        if (e) e->addRequest(floor);
    }

    void step() {
        for (auto e : elevators)
            e->move();
    }

    vector<ElevatorCar*>& getElevators() {
        return elevators;
    }
};

/* ===================== DISPATCHERS ===================== */

class InternalDispatcher {
    vector<ElevatorCar*>& elevators;

public:
    InternalDispatcher(vector<ElevatorCar*>& elevators)
        : elevators(elevators) {}

    void submitRequest(int elevatorId, int floor) {
        for (auto e : elevators) {
            if (e->id == elevatorId) {
                cout << "Internal request: Elevator "
                     << elevatorId << " -> Floor "
                     << floor << endl;
                e->addRequest(floor);
                return;
            }
        }
    }
};

class ExternalDispatcher {
    ElevatorController* controller;

public:
    ExternalDispatcher(ElevatorController* controller)
        : controller(controller) {}

    void submitRequest(int floor, Direction dir) {
        cout << "External request at floor "
             << floor << endl;
        controller->requestElevator(floor, dir);
    }
};

/* ===================== BUTTONS ===================== */

class InternalButton {
    InternalDispatcher* dispatcher;

public:
    InternalButton(InternalDispatcher* d)
        : dispatcher(d) {}

    void pressButton(int elevatorId, int floor) {
        dispatcher->submitRequest(elevatorId, floor);
    }
};

class ExternalButton {
    ExternalDispatcher* dispatcher;

public:
    ExternalButton(ExternalDispatcher* d)
        : dispatcher(d) {}

    void pressButton(int floor, Direction dir) {
        dispatcher->submitRequest(floor, dir);
    }
};

/* ===================== FLOOR ===================== */

class Floor {
public:
    int number;
    ExternalButton* button;

    Floor(int n, ExternalButton* b)
        : number(n), button(b) {}
};

/* ===================== BUILDING ===================== */

class Building {
public:
    vector<Floor> floors;
    ElevatorController controller;

    Building(int floorCount,
             ElevatorSelectionStrategy* strategy)
        : controller(strategy) {

        auto* extDispatcher =
            new ExternalDispatcher(&controller);
        auto* button =
            new ExternalButton(extDispatcher);

        for (int i = 0; i < floorCount; i++)
            floors.emplace_back(i, button);
    }
};

/* ===================== MAIN ===================== */

int main() {
    NearestElevatorStrategy strategy;
    ElevatorController controller(&strategy);

    ElevatorCar e1(1), e2(2);
    controller.addElevator(&e1);
    controller.addElevator(&e2);

    ExternalDispatcher extDisp(&controller);
    ExternalButton extBtn(&extDisp);

    InternalDispatcher intDisp(controller.getElevators());
    InternalButton intBtn(&intDisp);

    // External call
    extBtn.pressButton(3, Direction::UP);
    controller.step();

    // Internal call
    intBtn.pressButton(1, 7);
    controller.step();

    return 0;
}
