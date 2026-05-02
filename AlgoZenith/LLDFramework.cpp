#include<bits/stdc++.h>
using namespace std;


/*
Requirements -->design flow

Entities: -->aim for main apis
- Vehicle --> Vehicle class should have number and type
- ParkingSlot -->it have spotId,isFree and provide methods like park and unpark vehicle
- ParkingLot --> have core APIs like parkVehicle and unParkVehicle and displayAvailableSpots

code -->flow of classes and objects working +pattern 
*/ 

enum class VehicleType{
   CAR,
   BIKE,
   CYCLE
};
class Vehicle{
  public:
     string number;
     VehicleType type;

     Vehicle(string num,VehicleType type):number(num),type(type){}
};

class ParkingSpot{
   public:
      int spotId;
      bool isFree;
      Vehicle*vehicle;

      ParkingSpot(int id):spotId(id),vehicle(nullptr){}

      bool isAvailable(){
        return vehicle==nullptr;
      }

      bool ParkVehicle(Vehicle*v){
        if(!isFree){
            return false;
        }
        vehicle=v;
        return true;
      }
      void unParkVehicle(){
        vehicle=nullptr;
      }
};

class Parkinglot{
  public:
     vector<ParkingSpot*>spots;
     
     Parkinglot(int n){
        for(int i=1;i<=n;i++){
            spots.push_back(new ParkingSpot(i));
        }
     }

     void parkVehicle(Vehicle*v){
        for(auto spot:spots){
            if(!spot->isFree){
                spot->vehicle=v;
            }
        }
     }

      void unParkVehicle(string vehicleNumber) {

        for (auto spot : spots) {

            // Check occupied spot
            if (!spot->isAvailable() &&
                spot->vehicle->number == vehicleNumber) {

                spot->unParkVehicle();

                cout << "Vehicle "
                     << vehicleNumber
                     << " removed\n";

                return;
            }
        }

        cout << "Vehicle not found\n";
    }

     void displaySpots(){
        for(auto spot:spots){
            if(spot->isFree){
                cout<<spot->spotId;
            }
        }
     }

};

int main(){
    Parkinglot lot(5);

    Vehicle v1("TN03",VehicleType::CAR);
     Vehicle v2("TN04",VehicleType::CAR);

    lot.parkVehicle(&v1);
    lot.unParkVehicle("TN03");
    lot.displaySpots();
    
}