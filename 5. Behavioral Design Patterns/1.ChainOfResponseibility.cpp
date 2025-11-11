/*
client--> Handler -->Concrete handler
                        class1 ,class 2

*/#include <iostream>
#include <string>

using namespace std;

// Abstract Handler class
class Handler {
protected:
    Handler* next = nullptr;  // Pointer to next handler in chain
public:
    virtual ~Handler() {}

    void setNext(Handler* handler) {
        next = handler;
    }

    virtual void request(const string& req) {
        if (next) {
            next->request(req);
        } else {
            cout << "It's the last handle. Request: " << req << " cannot be processed." << endl;
        }
    }
};

// Concrete handler for low level requests
class LowLevelHandler : public Handler {
public:
    void request(const string& req) override {
        if (req == "low") {
            cout << "Handling the low level request." << endl;
        } else if (next) {
            next->request(req);
        } else {
            cout << "No handler available for request: " << req << endl;
        }
    }
};

// Concrete handler for high level requests
class HighLevelHandler : public Handler {
public:
    void request(const string& req) override {
        if (req == "high") {
            cout << "Handling the high level request." << endl;
        } else if (next) {
            next->request(req);
        } else {
            cout << "No handler available for request: " << req << endl;
        }
    }
};

int main() {
    LowLevelHandler low;
    HighLevelHandler high;

    // Set chain: low -> high
    low.setNext(&high);

    low.request("high");  // Will be handled by high level handler
    low.request("low");   // Will be handled by low level handler
    low.request("mid");   // No handler handles it, goes through chain till end

    return 0;
}
