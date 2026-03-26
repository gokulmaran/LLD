#include <bits/stdc++.h>
using namespace std;

// ✅ Step 1: Features
// 1. Park vehicle
// 2. Remove vehicle
// 3. Get available slots

// ✅ Step 2: Entities + Responsibilities
// Entities:
//   - Vehicle     → holds number, type
//   - ParkingSpot → holds vehicle, spotId, isFree
//   - ParkingLot  → manages all spots

// Responsibilities:
//   - ParkingSpot → assign/remove vehicle
//   - ParkingLot  → park/remove/find slots

// ✅ Step 2: Entities + Responsibilities
// Vehicle → number, type
// ParkingSpot → id, vehicle | assign(), remove(), isFree()
// ParkingLot → spots | park(), remove(), available()

// ✅ Step 3: Code Skeleton

class Vehicle {
public:
    string number;
    string type;

    Vehicle(string num, string t) : number(num), type(t) {}
};

class ParkingSpot {
public:
    int id;
    Vehicle* vehicle;

    ParkingSpot(int id) : id(id), vehicle(nullptr) {}

    bool isFree() {
        return vehicle == nullptr;
    }

    void assignVehicle(Vehicle* v) {
        vehicle = v;
    }

    void removeVehicle() {
        vehicle = nullptr;
    }
};

class ParkingLot {
private:
    vector<ParkingSpot*> spots;

public:
    ParkingLot(int n) {
        for (int i = 0; i < n; i++) {
            spots.push_back(new ParkingSpot(i));
        }
    }

    bool parkVehicle(Vehicle* v) {
        for (auto spot : spots) {
            if (spot->isFree()) {
                spot->assignVehicle(v);
                cout << "Parked at spot: " << spot->id << endl;
                return true;
            }
        }
        cout << "No free spots\n";
        return false;
    }

    bool removeVehicle(string vehicleNumber) {
        for (auto spot : spots) {
            if (!spot->isFree() && spot->vehicle->number == vehicleNumber) {
                spot->removeVehicle();
                cout << "Vehicle removed\n";
                return true;
            }
        }
        cout << "Vehicle not found\n";
        return false;
    }

    int getAvailableSpots() {
        int count = 0;
        for (auto spot : spots) {
            if (spot->isFree()) count++;
        }
        return count;
    }
};

// ✅ Step 4: Driver
int main() {
    ParkingLot lot(3);

    Vehicle v1("TN01", "Car");
    Vehicle v2("TN02", "Bike");

    lot.parkVehicle(&v1);
    lot.parkVehicle(&v2);

    cout << "Available spots: " << lot.getAvailableSpots() << endl;

    lot.removeVehicle("TN01");

    cout << "Available spots: " << lot.getAvailableSpots() << endl;

    return 0;
}
