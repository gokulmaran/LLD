#include <bits/stdc++.h>
using namespace std;
//flow api(data+state+change-->flow code)
class ParkingSpot {
public:
    int id;
    bool isOccupied;

    ParkingSpot(int id) {
        this->id = id;
        this->isOccupied = false;
    }
};

class ParkingLot {
private:
    vector<ParkingSpot> spots;
    unordered_map<string, int> vehicleToSpot; // vehicleId -> spotId

public:
    ParkingLot(int n) {
        for (int i = 0; i < n; i++) {
            spots.push_back(ParkingSpot(i));
        }
    }

    // Park vehicle
    bool parkVehicle(string vehicleId) {
        // already parked check
        if (vehicleToSpot.count(vehicleId)) {
            cout << "Vehicle already parked\n";
            return false;
        }

        for (auto &spot : spots) {
            if (!spot.isOccupied) {
                spot.isOccupied = true;
                vehicleToSpot[vehicleId] = spot.id;

                cout << "Vehicle " << vehicleId 
                     << " parked at spot " << spot.id << endl;
                return true;
            }
        }

        cout << "No available spots\n";
        return false;
    }

    // Unpark vehicle
    bool unparkVehicle(string vehicleId) {
        if (!vehicleToSpot.count(vehicleId)) {
            cout << "Vehicle not found\n";
            return false;
        }

        int spotId = vehicleToSpot[vehicleId];
        spots[spotId].isOccupied = false;

        vehicleToSpot.erase(vehicleId);

        cout << "Vehicle " << vehicleId 
             << " removed from spot " << spotId << endl;

        return true;
    }

    // Get available spots count
    int getAvailableSpots() {
        int count = 0;
        for (auto &spot : spots) {
            if (!spot.isOccupied) {
                count++;
            }
        }
        return count;
    }
};

int main() {
    ParkingLot lot(3);

    lot.parkVehicle("TN01");
    lot.parkVehicle("TN02");

    cout << "Available spots: " 
         << lot.getAvailableSpots() << endl;

    lot.unparkVehicle("TN01");

    cout << "Available spots: " 
         << lot.getAvailableSpots() << endl;

    return 0;
}