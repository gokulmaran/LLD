/*
Features
1. The parking lot should have multiple levels, each level with a certain number of parking spots.
2. The parking lot should support different types of vehicles, such as cars, motorcycles, and trucks.
3. Each parking spot should be able to accommodate a specific type of vehicle.
4. The system should assign a parking spot to a vehicle upon entry and release it when the vehicle exits.
5. The system should track the availability of parking spots and provide real-time information to customers.
6. The system should handle multiple entry and exit points and support concurrent access.

Entities
1. Vehicle class should be absstract class should be inherited by car,bike,
2. Parking lot class follows the singleton pattern to ensure only one instance of parkig lot exists.It maintains a list of levels and provide methods to park ad unpark vehicles
3. Parking Spot class respresents an individual parking spot nad tracks the availability using parked and unparked vehicle
4. The Entry gate class Handles vehicle entry,ticket generation and spot type
5. The Exit Gate class handles the vehicle exit, cost computation should have  happened,strategies for cost computation likeFixed price,hourly based computation
6. The ticket class should stores the entry time, vehicle info, spot assignment
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std;

/* ================= ENUMS ================= */

enum class VehicleType { CAR, BIKE, TRUCK };
enum class SpotType { SMALL, MEDIUM, LARGE };

/* ================= VEHICLE ================= */

class Vehicle {
public:
    string number;
    VehicleType type;

    Vehicle(string number, VehicleType v)
        : number(number), type(v) {}

    VehicleType getType() {
        return type;
    }

    string getNumber() {
        return number;
    }

    virtual ~Vehicle() {}
};

class Car : public Vehicle {
public:
    Car(string number)
        : Vehicle(number, VehicleType::CAR) {}
};

class Bike : public Vehicle {
public:
    Bike(string number)
        : Vehicle(number, VehicleType::BIKE) {}
};

/* ================= PARKING SPOT ================= */

class ParkingSpot {
public:
    SpotType type;
    Vehicle* vehicle;

    ParkingSpot(SpotType t)
        : type(t), vehicle(nullptr) {}

    bool isFree() {
        return vehicle == nullptr;
    }

    bool canFit(VehicleType v) {
        if (v == VehicleType::BIKE) return true;

        if (v == VehicleType::CAR && type != SpotType::SMALL)
            return true;

        if (v == VehicleType::TRUCK && type == SpotType::LARGE)
            return true;

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

/* ================= PRICING ================= */

class PricingStrategy {
public:
    virtual double calculate(time_t entry, time_t exitTime) = 0;
    virtual ~PricingStrategy() {}
};

class HourlyPricing : public PricingStrategy {
public:
    double calculate(time_t entry, time_t exitTime) override {
        double hrs = difftime(exitTime, entry) / 3600.0;
        return ceil(hrs) * 50;
    }
};

/* ================= PAYMENT ================= */

class PaymentStrategy {
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentStrategy() {}
};

class CashPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        cout << "Payment Successful: ₹" << amount << " via Cash\n";
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

    lot.addSpot(new ParkingSpot(SpotType::SMALL));
    lot.addSpot(new ParkingSpot(SpotType::MEDIUM));
    lot.addSpot(new ParkingSpot(SpotType::LARGE));

    Vehicle* car = new Car("TN-01-1234");

    Ticket* ticket = lot.parkVehicle(car);

    this_thread::sleep_for(chrono::seconds(2));

    if (ticket)
        lot.exitVehicle(ticket);

    delete car;

    return 0;
}