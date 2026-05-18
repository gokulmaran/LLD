#include <bits/stdc++.h>
using namespace std;
/*
Parking lot
1)Vehicle should be enter into parking spot
2)Once spot vacant vehicle need to be parked based on vehicle type
3)Parking spot should be manage the park and unpark the vhicles and spots available
4)Parking lot should contain multple spots adn park the vehicle and unpark vehicle

Entites
Vehicle-->name, number,type
Parkingspot-->spotid,park() and unpark()
Parkinglot-->park(),unpark(),displaySpots()
*/

enum class VehicleType{
   CAR,
   BIKE, 
};
class Vehicle{
  public:
     string name;
     string number;
     VehicleType type;
     Vehicle(string name,string number,VehicleType type){
        this->name=name;
        this->number=number;
        this->type=type;
     }
};

class ParkingSpot{
   public:
      int spotId;
      Vehicle*vehicle;
      bool isFree=false;

      ParkingSpot(int id):spotId(id),vehicle(nullptr),isFree(true){}

      void parkVehicle(Vehicle*v){
         vehicle=v;
         isFree=false;
      }

      void unParkVehicle(Vehicle*v){
         v=nullptr;
         isFree=true;
      }
      bool isFreeSpt(){
        return isFree;
      }
      Vehicle*checkVehicle(){
        return vehicle;
      }
};

class PaymentStrategy{
  public:
     virtual void Pay(int amt)=0;
};

class UPI:public PaymentStrategy{
  public:
     void Pay(int amt){
        cout<<"Amt paid "<<amt<<" using UPI"<<endl;
     }
};
class Parkinglot{
  public:
      vector<ParkingSpot*>spots;
      PaymentStrategy *strategy;

      Parkinglot(int id,PaymentStrategy*pStrategy){
        strategy=pStrategy;
        for(int i=1;i<=id;i++){
            spots.push_back(new ParkingSpot(i));
        }
      }
      
      void parkVehicle(Vehicle*v){
        for(auto it:spots){
            if(it->isFreeSpt()){
                it->parkVehicle(v);
                cout<<"Vehicle "<<v->number<<" parked successfully"<<endl;
                break;
            }
        }
        
      }

      void unparkVehicle(string vNumber,int amount){
          for(auto it:spots){
            auto vehicle=it->checkVehicle();
            if(vehicle!=nullptr and vehicle->number==vNumber){
                it->unParkVehicle(vehicle);
                strategy->Pay(amount);
                cout<<"Vehicle "<<vehicle->number<<" unparked successfully"<<endl;
            }
          }
      }

      void displaySpots(){
        int cnt=0;
        for(auto it:spots){
            if(it->isFreeSpt()){
            cnt++;
            }
        }
        cout<<cnt<<" spots available"<<endl;
      }
};

int main(){
    Vehicle* v1=new Vehicle("CAR","TN35",VehicleType::CAR);
    Vehicle* v2=new Vehicle("CAR","TN37",VehicleType::BIKE);
    PaymentStrategy*payment =new UPI();
    Parkinglot lot(5,payment);
    lot.parkVehicle(v1);
    lot.unparkVehicle("TN35",100);
    lot.displaySpots();
    lot.parkVehicle(v2);
    lot.unparkVehicle("TN37",10);
    lot.displaySpots();
}
