#include <iostream>
#include <string>

// 1. Delivery Strategy Interface
class NotificationStrategy {
public:
    virtual ~NotificationStrategy() {}
    virtual void send(std::string message, std::string recipient) = 0;
};

// 2. Concrete Delivery Strategies
class EmailStrategy : public NotificationStrategy {
public:
    void send(std::string msg, std::string recipient) override {
        std::cout << "[Email] Sending to " << recipient << ": " << msg << "\n";
    }
};

class SMSStrategy : public NotificationStrategy {
public:
    void send(std::string msg, std::string recipient) override {
        std::cout << "[SMS] Sending to " << recipient << ": " << msg << "\n";
    }
};

// 3. Notification Manager (Context)
class NotificationService {
private:
    NotificationStrategy* strategy;

public:
    NotificationService() : strategy(nullptr) {}

    // Proper memory management: delete old strategy before setting new one
    void setStrategy(NotificationStrategy* newStrategy) {
        if (strategy != nullptr) {
            delete strategy;
        }
        strategy = newStrategy;
    }

    void notify(std::string message, std::string recipient) {
        if (strategy != nullptr) {
            strategy->send(message, recipient);
        } else {
            std::cout << "Error: No notification strategy set!\n";
        }
    }

    // Destructor to clean up the final strategy
    ~NotificationService() {
        if (strategy != nullptr) {
            delete strategy;
        }
    }
};

int main() {
    NotificationService service;

    // Send via Email
    // We pass a new object; the Service now owns this pointer
    service.setStrategy(new EmailStrategy());
    service.notify("Your order has shipped!", "user@example.com");

    // Switch to SMS at runtime
    // The Service will delete the EmailStrategy before taking the SMSStrategy
    service.setStrategy(new SMSStrategy());
    service.notify("OTP: 123456", "+91 9876543210");

    return 0;
}
