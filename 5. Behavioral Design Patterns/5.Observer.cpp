#include <bits/stdc++.h>
using namespace std;

// Observer Interface
class Observer {
public:
    virtual void update(int state) = 0;
    virtual ~Observer() = default;
};

// Subject
class Subject {
private:
    vector<Observer*> observers;
    int state;

public:
    void setState(int s) {
        state = s;
        notify();
    }

    void attach(Observer* obs) {
        observers.push_back(obs);
    }

    void detach(Observer* obs) {
        auto it = find(observers.begin(), observers.end(), obs);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void notify() {
        for (auto os : observers) {
            os->update(state);
        }
    }
};

// Concrete Observer
class ConcreteObserver : public Observer {
private:
    string name;

public:
    ConcreteObserver(string name) : name(name) {}

    void update(int state) override {
        cout << name << " notified. New state: " << state << endl;
    }
};

int main() {
    Subject sub;

    ConcreteObserver obs1("Observer1");
    ConcreteObserver obs2("Observer2");

    sub.attach(&obs1);
    sub.attach(&obs2);

    sub.setState(10);
}