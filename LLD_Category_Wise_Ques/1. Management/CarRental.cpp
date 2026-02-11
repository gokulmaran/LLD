#include <iostream>
#include <string>
#include <vector>

// ======================= MODELS =======================

enum class VehicleType {
    CAR,
    BIKE
};

class Vehicle {
    std::string vehicleId;
    VehicleType type;
    bool available;

public:
    Vehicle(const std::string& id, VehicleType t)
        : vehicleId(id), type(t), available(true) {}

    std::string getId() const { return vehicleId; }
    VehicleType getType() const { return type; }
    bool isAvailable() const { return available; }
    void setAvailable(bool status) { available = status; }
};

class User {
    std::string userId;
    std::string name;

public:
    User(const std::string& id, const std::string& name)
        : userId(id), name(name) {}

    std::string getId() const { return userId; }
    std::string getName() const { return name; }
};

// ======================= INVENTORY =======================

class VehicleInventory {
    std::vector<Vehicle*> vehicles; // store owns vehicles

public:
    ~VehicleInventory() {
        for (auto v : vehicles) delete v;
    }

    void addVehicle(Vehicle* vehicle) {
        vehicles.push_back(vehicle);
    }

    Vehicle* getAvailableVehicle(VehicleType type) {
        for (auto v : vehicles) {
            if (v->getType() == type && v->isAvailable()) {
                return v;
            }
        }
        return nullptr;
    }
};

// ======================= RESERVATION =======================

class Reservation {
    User* user;        // not owned
    Vehicle* vehicle;  // not owned
    int durationHours;

public:
    Reservation(User* u, Vehicle* v, int hours)
        : user(u), vehicle(v), durationHours(hours) {
        vehicle->setAvailable(false);
    }

    int getDuration() const { return durationHours; }
    Vehicle* getVehicle() const { return vehicle; }
};

// ======================= BILLING (STRATEGY) =======================

class Bill {
public:
    virtual double calculateAmount(const Reservation& reservation) = 0;
    virtual ~Bill() = default;
};

class HourlyBill : public Bill {
public:
    double calculateAmount(const Reservation& reservation) override {
        return reservation.getDuration() * 100.0; // ₹100/hour
    }
};

// ======================= PAYMENT (STRATEGY) =======================

class PaymentStrategy {
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentStrategy() = default;
};

class CardPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        std::cout << "Paid ₹" << amount << " using Card\n";
    }
};

// ======================= STORE =======================

class Store {
    VehicleInventory inventory;

public:
    VehicleInventory& getInventory() { return inventory; }
};

// ======================= SYSTEM =======================

class VehicleRentalSystem {
    Store store;

public:
    Store& getStore() { return store; }
};

// ======================= DEMO (MAIN) =======================

int main() {
    VehicleRentalSystem system;

    // Add vehicle (ownership with inventory)
    system.getStore().getInventory().addVehicle(
        new Vehicle("CAR-101", VehicleType::CAR)
    );

    // Create user (stack allocation)
    User user("U1", "Gokul");

    // Get vehicle
    Vehicle* vehicle =
        system.getStore().getInventory().getAvailableVehicle(VehicleType::CAR);

    if (!vehicle) {
        std::cout << "No vehicle available\n";
        return 0;
    }

    // Reservation
    Reservation reservation(&user, vehicle, 5);

    // Billing
    HourlyBill bill;
    double amount = bill.calculateAmount(reservation);

    // Payment
    CardPayment payment;
    payment.pay(amount);

    return 0;
}
