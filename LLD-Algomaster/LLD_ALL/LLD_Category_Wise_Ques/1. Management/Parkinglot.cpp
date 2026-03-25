#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep((x) * 1000)
#else
#include <unistd.h>
#endif

using namespace std;

/* ================= ENUMS ================= */

enum class VehicleType { BIKE, CAR, TRUCK };
enum class SpotType { SMALL, MEDIUM, LARGE };

/* ================= VEHICLE ================= */

class Vehicle {
protected:
    string number;
    VehicleType type;

public:
    Vehicle(string num, VehicleType t) : number(num), type(t) {}
    virtual ~Vehicle() {}

    VehicleType getType() const { return type; }
    string getNumber() const { return number; }
};

class Car : public Vehicle {
public:
    Car(string num) : Vehicle(num, VehicleType::CAR) {}
};

class Bike : public Vehicle {
public:
    Bike(string num) : Vehicle(num, VehicleType::BIKE) {}
};

/* ================= PARKING SPOT ================= */

class ParkingSpot {
protected:
    SpotType type;
    Vehicle* vehicle;

public:
    ParkingSpot(SpotType t) : type(t), vehicle(nullptr) {}
    virtual ~ParkingSpot() {}

    bool isFree() const {
        return vehicle == nullptr;
    }

    bool canFit(VehicleType v) {
        if (v == VehicleType::BIKE) return true;
        if (v == VehicleType::CAR && type != SpotType::SMALL) return true;
        if (v == VehicleType::TRUCK && type == SpotType::LARGE) return true;
        return false;
    }

    void park(Vehicle* v) {
        vehicle = v;
    }

    void unpark() {
        vehicle = nullptr;
    }
};

/* ================= TICKET ================= */

class Ticket {
public:
    int ticketId;
    time_t entryTime;
    ParkingSpot* spot;
    Vehicle* vehicle;

    Ticket(int id, Vehicle* v, ParkingSpot* s)
        : ticketId(id), vehicle(v), spot(s) {
        entryTime = time(nullptr);
    }
};

/* ================= PRICING STRATEGY ================= */

class PricingStrategy {
public:
    virtual double calculate(time_t entry, time_t exitTime) = 0;
    virtual ~PricingStrategy() {}
};

class HourlyPricing : public PricingStrategy {
public:
    double calculate(time_t entry, time_t exitTime) override {
        double hours = difftime(exitTime, entry) / 3600.0;
        return ceil(hours) * 50; // ₹50 per hour
    }
};

/* ================= PAYMENT STRATEGY ================= */

class PaymentStrategy {
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentStrategy() {}
};

class CashPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Payment Successful: ₹" << amount << " via Cash" << endl;
    }
};

/* ================= ENTRY GATE ================= */

class EntryGate {
    int ticketCounter = 0;

public:
    Ticket* generateTicket(Vehicle* v, ParkingSpot* s) {
        cout << "Vehicle Parked. Ticket Generated.\n";
        return new Ticket(++ticketCounter, v, s);
    }
};

/* ================= EXIT GATE ================= */

class ExitGate {
public:
    void processExit(Ticket* ticket,
                     PricingStrategy* pricing,
                     PaymentStrategy* payment) {

        time_t exitTime = time(nullptr);
        double fee = pricing->calculate(ticket->entryTime, exitTime);

        payment->pay(fee);
        ticket->spot->unpark();

        cout << "Vehicle Exited Successfully.\n";
    }
};

/* ================= PARKING LOT (SINGLETON) ================= */

class ParkingLot {
private:
    vector<ParkingSpot*> spots;
    EntryGate entryGate;
    ExitGate exitGate;

    ParkingLot() {}

public:
    static ParkingLot& getInstance() {
        static ParkingLot instance;
        return instance;
    }

    void addSpot(ParkingSpot* spot) {
        spots.push_back(spot);
    }

    ParkingSpot* findSpot(VehicleType v) {
        for (auto spot : spots) {
            if (spot->isFree() && spot->canFit(v))
                return spot;
        }
        return nullptr;
    }

    Ticket* parkVehicle(Vehicle* v) {
        ParkingSpot* spot = findSpot(v->getType());
        if (!spot) {
            cout << "No Parking Spot Available\n";
            return nullptr;
        }
        spot->park(v);
        return entryGate.generateTicket(v, spot);
    }

    void exitVehicle(Ticket* ticket) {
        PricingStrategy* pricing = new HourlyPricing();
        PaymentStrategy* payment = new CashPayment();

        exitGate.processExit(ticket, pricing, payment);

        delete pricing;
        delete payment;
        delete ticket;
    }
};

/* ================= MAIN ================= */

int main() {
    ParkingLot& lot = ParkingLot::getInstance();

    // Add parking spots
    lot.addSpot(new ParkingSpot(SpotType::SMALL));
    lot.addSpot(new ParkingSpot(SpotType::MEDIUM));
    lot.addSpot(new ParkingSpot(SpotType::LARGE));

    // Create vehicle
    Vehicle* car = new Car("TN-01-1234");

    // Park vehicle
    Ticket* ticket = lot.parkVehicle(car);

    // Simulate parking time
    sleep(2);

    // Exit vehicle
    if (ticket)
        lot.exitVehicle(ticket);

    delete car;
    return 0;
}
