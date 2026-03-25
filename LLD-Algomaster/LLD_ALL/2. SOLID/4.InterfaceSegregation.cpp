#include <iostream>
#include <vector>
using namespace std;

/*ISP--Clients should not be forced to depend on interfaces they do not use. Instead of
one fat interface with many unrelated methods, we split it into smaller, specific
interfaces. This keeps classes clean and focused.
*/

class Workable {
public:
    virtual void work() = 0;
    virtual ~Workable(){};
};

class Eatable {
public:
    virtual void eat() = 0;
    virtual ~Eatable(){};
};

class HumanWorker : public Workable, public Eatable {
public:
    void work() override {
        cout << "Human is working..." << std::endl;
    }

    void eat() override {
       cout << "Human is eating..." << std::endl;
    }
};

class RobotWorker : public Workable {
public:
    void work() override {
        cout << "Robot is working..." << std::endl;
    }
};

int main() {
    HumanWorker human;
    human.work();
    human.eat();

    RobotWorker robot;
    robot.work();

    // Demonstrate polymorphism
    std::vector<Workable*> workers = {&human, &robot};
    for (auto worker : workers) {
        worker->work();
    }

    return 0;
}