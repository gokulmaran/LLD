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
2. Parking lot class follows the singleton pattern to ensure only one instance of parkig lot exists.
It maintains a add spots and find spots and allows the park vehicle and exit the vehicle
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
//============================================
/*
#include <bits/stdc++.h>
using namespace std;

//
// 🚗 Vehicle
//

enum class VehicleType {
    BIKE,
    CAR
};

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
    Car(string number) : Vehicle(number, VehicleType::CAR) {}
};

class Bike : public Vehicle {
public:
    Bike(string number) : Vehicle(number, VehicleType::BIKE) {}
};

//
// 🅿️ ParkingSpot
//

enum class SpotType {
    BIKE,
    CAR
};

class ParkingSpot {
    int id;
    SpotType type;
    bool isFree;
    Vehicle* vehicle;

public:
    ParkingSpot(int id, SpotType type)
        : id(id), type(type), isFree(true), vehicle(nullptr) {}

    bool canPark(Vehicle* v) {
        if (type == SpotType::CAR && v->getType() == VehicleType::CAR)
            return true;
        if (type == SpotType::BIKE && v->getType() == VehicleType::BIKE)
            return true;
        return false;
    }

    bool park(Vehicle* v) {
        if (!isFree || !canPark(v)) return false;
        vehicle = v;
        isFree = false;
        return true;
    }

    void unpark() {
        vehicle = nullptr;
        isFree = true;
    }

    bool free() const { return isFree; }
    int getId() const { return id; }
};

//
// 🎫 Ticket
//

class Ticket {
public:
    Vehicle* vehicle;
    ParkingSpot* spot;
    time_t entryTime;

    Ticket(Vehicle* v, ParkingSpot* s)
        : vehicle(v), spot(s) {
        entryTime = time(nullptr);
    }
};

//
// 💰 Payment Strategy
//

class PaymentStrategy {
public:
    virtual int calculateFare(time_t entryTime) = 0;
    virtual ~PaymentStrategy() {}
};

class HourlyPayment : public PaymentStrategy {
public:
    int calculateFare(time_t entryTime) override {
        time_t now = time(nullptr);
        int hours = difftime(now, entryTime) / 3600;

        if (hours == 0) hours = 1;
        return hours * 10;
    }
};

//
// 🏬 ParkingLot
//

class ParkingLot {
    vector<ParkingSpot*> spots;

public:
    ParkingLot(int carSpots, int bikeSpots) {
        int id = 0;

        for (int i = 0; i < carSpots; i++)
            spots.push_back(new ParkingSpot(id++, SpotType::CAR));

        for (int i = 0; i < bikeSpots; i++)
            spots.push_back(new ParkingSpot(id++, SpotType::BIKE));
    }

    Ticket* parkVehicle(Vehicle* v) {
        for (auto spot : spots) {
            if (spot->free() && spot->canPark(v)) {
                spot->park(v);
                return new Ticket(v, spot);
            }
        }
        return nullptr;
    }

    int unparkVehicle(Ticket* ticket, PaymentStrategy* strategy) {
        ticket->spot->unpark();
        return strategy->calculateFare(ticket->entryTime);
    }
};

//
// 🚀 Main
//

int main() {
    ParkingLot lot(2, 2);

    Vehicle* car = new Car("TN01AB1234");
    Vehicle* bike = new Bike("TN02XY5678");

    Ticket* t1 = lot.parkVehicle(car);
    Ticket* t2 = lot.parkVehicle(bike);

    if (t1)
        cout << "Car parked at spot: " << t1->spot->getId() << endl;

    if (t2)
        cout << "Bike parked at spot: " << t2->spot->getId() << endl;

    sleep(2);

    PaymentStrategy* payment = new HourlyPayment();

    int fare1 = lot.unparkVehicle(t1, payment);
    cout << "Car Fare: " << fare1 << endl;

    int fare2 = lot.unparkVehicle(t2, payment);
    cout << "Bike Fare: " << fare2 << endl;

    return 0;
}
*/
//==================================================================================
/*
#include<bits/stdc++.h>
using namespace std;
//Parking lot system

//Vehicle- It has vehicle type and number of car and bike
//Parking spot- It will responsible for park and unpark vehicle and canfit the vehicle
//Ticket --need to be generated with entry time
//Entry gate-ticket need to be genrated while vehicle reinterpret_cast
//Exit gate--> based on vehicle exits we need to calculate the price and send atof(strategy pattern)
//Parking lot-->It should be singleton class where we need to add spots and aaprk and unpark vehicle
//main --Using parkinglot object will park and unpark vehicle and ticket need to be generated

//enums
enum class VehicleType{BIKE,CAR,TRUCK};
enum class SpotType{SMALL,MEDIUM,LARGE};

//Vehicle class
class Vehicle{
  public:
     VehicleType type;
     string number;
    
    Vehicle(string number,VehicleType v):number(number),type(v){}
    
    string getNumber(){
      return number;
    }
    
    VehicleType getType(){
      return type;
    }
};
class Car: public Vehicle{
  public:
     Car(string num): Vehicle(num,VehicleType::CAR) {}
};
class Bike: public Vehicle{
  public:
     Bike(string num): Vehicle(num,VehicleType::BIKE) {}
};
//Parking spot
class ParkingSpot{
  public:
    Vehicle*vehicle;
    SpotType type;
    ParkingSpot(SpotType t): type(t),vehicle(nullptr) {}
    
    bool isFree(){
      return vehicle==nullptr;
    }
    void park(Vehicle*v){
      vehicle=v;
    }
    void unPark(){
      vehicle=nullptr;
    }
    bool canFit(VehicleType v){
      if(v==VehicleType::BIKE) return true;
      if(v==VehicleType::CAR and type!=SpotType::SMALL) return true;
      if(v==VehicleType::TRUCK and type==SpotType::LARGE) return true;
      return false;
    }
};

//ticket
class Ticket{
  public:
     int ticketId;
     time_t entryTime;
     ParkingSpot*spot;
     Vehicle*vehicle;
     
     Ticket(int id,Vehicle*v,ParkingSpot*s):ticketId(id),vehicle(v),spot(s){
        entryTime=time(nullptr); 
     }
};

class EntryGate{
  public:
     int ticketCounter=0;
     
     Ticket* generateTicket(Vehicle*v,ParkingSpot*s){
         cout << "Vehicle Parked. Ticket Generated.\n";
       return new Ticket(++ticketCounter,v,s);
     }
};

//pricing strategy
class PricingStrategy{
  public:
     virtual double calculate(time_t startTime,time_t endTime)=0;
};
class HrlyPricingStrategy: public PricingStrategy{
  public:
     double calculate (time_t startTime,time_t endTime){
        double hrs = difftime(endTime, startTime) / 3600.0;
        return ceil(hrs) * 50;
     }
};

class PaymentStrategy{
  public:
    virtual void pay(double amt)=0;
};
class CashPayment: public PaymentStrategy{
  public:
    void pay(double amt){
      cout<<"Amount "<<amt<<" paid successfully"<<endl;
    }
};
class ExitGate{
  public: 
    void exitGate(Ticket*t,PricingStrategy*p,PaymentStrategy*p1){
      time_t exitTime=time(nullptr);
      double price=p->calculate(t->entryTime,exitTime);
      p1->pay(price);
      t->spot->unPark();
      cout<<"Vehicle Exited successsfully";
    }
     
};
class Parkinglot{
  public:
     vector<ParkingSpot*>v;
     EntryGate entry;
     ExitGate exit1;
     
     static Parkinglot& getInstance(){
       static Parkinglot instance;
       return instance;
     }
     
     void addSpot(ParkingSpot*p){
       v.push_back(p);
     }
     
     Ticket*ParkVehicle(Vehicle*v){
       ParkingSpot*s=findSpot(v->getType());
       
       if(!s){
          cout << "No Parking Spot Available\n";
          return nullptr;
       }
       s->park(v);
        return entry.generateTicket(v, s);
     }
     
     void exitVehicle(Ticket*ticket){
       PricingStrategy*price=new HrlyPricingStrategy();
       PaymentStrategy*payment=new CashPayment();
       
       exit1.exitGate(ticket,price,payment);
     }
    private:
      ParkingSpot*findSpot(VehicleType type){
        for(auto s:v){
          if(s->isFree() and s->canFit(type)){
            return s;
          }
        }
        return nullptr;
      }
};

int main() 
{
    Parkinglot &lot=Parkinglot::getInstance();
    
    lot.addSpot(new ParkingSpot(SpotType::SMALL));
    lot.addSpot(new ParkingSpot(SpotType::LARGE));
    lot.addSpot(new ParkingSpot(SpotType::MEDIUM));
    
    Vehicle*car=new Car("TN-63810");
    
    Ticket*ticket=lot.ParkVehicle(car);
    
    this_thread::sleep_for(chrono::seconds(2));
    if(ticket){
      lot.exitVehicle(ticket);
    }
    
    
}
*/
