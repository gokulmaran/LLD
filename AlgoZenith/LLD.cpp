#include <bits/stdc++.h>
using namespace std;

/* Book My Show
Requirements
1. User able to search movies and view available show times
2. system should able to show available seats of selected movies
3. user able to select one or more seats to book the ticket
4. system able to complete their booking by processing payment to booked state

Entities (relationships and func-think main api code for arguments)
Movie- id,name
Seat- seatId,screenId,seatNumber,seatType
show- Movie,seats | it will get inserted
payment strategy-->pay()
BookingService-->book Seats(show,seats,Payments)
*/
class Movie{
  public:
     string name;
     Movie(string name):name(name){}
};

class Seat{
  public:
  int id;
  bool isBooked;

  Seat(int id):id(id),isBooked(false){}
};

class Show{
  public:
     Movie*movie;
     vector<Seat*>seats;

     Show(Movie*m,int totalSeats): movie(m){
        for(int i=0;i<totalSeats;i++){
            seats.push_back(new Seat(i));
        }
     }
};

class PaymentStrategy{
  public:
     virtual bool pay(double amount)=0;
};

class UPI:public PaymentStrategy{
  public:
     bool pay(double amount){
        cout<<"Paid the "<<amount<<"via UPI "<<endl;
        return true;
     }
};
class BookingService{
  public:
     bool bookSeats(Show*show,vector<int>seatIds,PaymentStrategy*payment){
         // 1. check availability
        for (int id : seatIds) {
            if (show->seats[id]->isBooked)
                return false;
        }

        // 2. payment
        int amount = seatIds.size() * 100;
        if (!payment->pay(amount))
            return false;

        // 3. mark booked
        for (int id : seatIds) {
            show->seats[id]->isBooked = true;
        }

        return true;
     }
};

int main(){
   Movie* movie = new Movie("Inception");
    Show* show = new Show(movie, 5);

   BookingService service;
    PaymentStrategy* payment = new UPI();

    if (service.bookSeats(show, {1,2,3,4,5}, payment))
        cout << "Booking Success\n";
    else
        cout << "Booking Failed\n";

}
/////////////////////////////////////