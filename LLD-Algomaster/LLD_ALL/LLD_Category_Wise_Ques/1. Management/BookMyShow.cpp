#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

/* ===================== ENUMS ===================== */

enum class City { CHENNAI, BANGALORE };

enum class SeatCategory { SILVER, GOLD, PLATINUM };

enum class BookingStatus { CREATED, CONFIRMED, CANCELLED };

enum class PaymentMode { UPI, CARD };

enum class PaymentStatus { SUCCESS, FAILED };

/* ===================== SEAT ===================== */

class Seat {
public:
    int seatId;
    SeatCategory category;
    bool isBooked;

    Seat(int id, SeatCategory cat)
        : seatId(id), category(cat), isBooked(false) {}
};

/* ===================== SCREEN ===================== */

class Screen {
public:
    int screenId;
    vector<Seat*> seats;

    Screen(int id) : screenId(id) {}
};

/* ===================== MOVIE ===================== */

class Movie {
public:
    int movieId;
    string name;
    int duration;

    Movie(int id, string n, int d)
        : movieId(id), name(n), duration(d) {}
};

/* ===================== SHOW ===================== */

class Show {
public:
    int showId;
    Movie* movie;
    Screen* screen;
    string startTime;

    Show(int id, Movie* m, Screen* s, string time)
        : showId(id), movie(m), screen(s), startTime(time) {}
};

/* ===================== THEATRE ===================== */

class Theatre {
public:
    int theatreId;
    string name;
    City city;
    vector<Screen*> screens;
    vector<Show*> shows;

    Theatre(int id, string n, City c)
        : theatreId(id), name(n), city(c) {}
};

/* ===================== CUSTOMER ===================== */

class Customer {
public:
    int customerId;
    string name;

    Customer(int id, string n)
        : customerId(id), name(n) {}
};

/* ===================== PAYMENT ===================== */

class Payment {
public:
    int paymentId;
    PaymentMode mode;
    PaymentStatus status;

    Payment(int id, PaymentMode m)
        : paymentId(id), mode(m), status(PaymentStatus::SUCCESS) {}
};

/* ===================== BOOKING ===================== */

class Booking {
public:
    int bookingId;
    Customer* customer;
    Show* show;
    vector<Seat*> bookedSeats;
    BookingStatus status;
    Payment* payment;

    Booking(int id, Customer* c, Show* s)
        : bookingId(id), customer(c), show(s),
          status(BookingStatus::CREATED), payment(nullptr) {}
};

/* ===================== MOVIE CONTROLLER ===================== */

class MovieController {
    unordered_map<City, vector<Movie*>> cityMovies;

public:
    void addMovie(Movie* movie, City city) {
        cityMovies[city].push_back(movie);
    }

    vector<Movie*> getMoviesByCity(City city) {
        return cityMovies[city];
    }
};

/* ===================== THEATRE CONTROLLER ===================== */

class TheatreController {
    unordered_map<City, vector<Theatre*>> cityTheatres;

public:
    void addTheatre(Theatre* theatre, City city) {
        cityTheatres[city].push_back(theatre);
    }

    vector<Theatre*> getTheatresByCity(City city) {
        return cityTheatres[city];
    }
};

/* ===================== MAIN APP ===================== */

int main() {
    // Controllers
    MovieController movieController;
    TheatreController theatreController;

    // Movie
    Movie* movie = new Movie(1, "Inception", 150);
    movieController.addMovie(movie, City::CHENNAI);

    // Theatre & Screen
    Theatre* theatre = new Theatre(1, "PVR", City::CHENNAI);
    Screen* screen = new Screen(1);

    // Seats
    for (int i = 1; i <= 5; i++)
        screen->seats.push_back(new Seat(i, SeatCategory::GOLD));

    theatre->screens.push_back(screen);

    // Show
    Show* show = new Show(1, movie, screen, "6:00 PM");
    theatre->shows.push_back(show);
    theatreController.addTheatre(theatre, City::CHENNAI);

    // Customer
    Customer* customer = new Customer(1, "Gokul");

    // Booking
    Booking* booking = new Booking(1, customer, show);
    booking->bookedSeats.push_back(screen->seats[0]);
    screen->seats[0]->isBooked = true;

    // Payment
    Payment* payment = new Payment(1, PaymentMode::UPI);
    booking->payment = payment;
    booking->status = BookingStatus::CONFIRMED;

    cout << "Booking Confirmed for "
         << booking->customer->name
         << " | Movie: " << movie->name << endl;

    return 0;
}
/*
#include <bits/stdc++.h>
#include <mutex>
using namespace std;

// ---------------- ENUMS ---------------- 

enum class SeatType { NORMAL, PREMIUM, VIP };
enum class SeatStatus { AVAILABLE, LOCKED, BOOKED };
enum class PaymentStatus { PENDING, SUCCESS, FAILED };

//---------------- SEAT ---------------- 

class Seat {
private:
    string seatId;
    SeatType type;
    SeatStatus status;
    mutex mtx;

public:
    Seat(string id, SeatType t)
        : seatId(id), type(t), status(SeatStatus::AVAILABLE) {}

    string getId() { return seatId; }

    SeatStatus getStatus() { return status; }

    bool lockSeat() {
        lock_guard<mutex> lock(mtx);
        if (status == SeatStatus::AVAILABLE) {
            status = SeatStatus::LOCKED;
            return true;
        }
        return false;
    }

    void bookSeat() {
        lock_guard<mutex> lock(mtx);
        status = SeatStatus::BOOKED;
    }
};

//---------------- SCREEN ---------------- 

class Screen {
private:
    string screenId;
    vector<Seat*> seats;

public:
    Screen(string id) : screenId(id) {}

    void addSeat(Seat* seat) {
        seats.push_back(seat);
    }

    vector<Seat*> getSeats() { return seats; }
};

// ---------------- MOVIE ---------------- 

class Movie {
private:
    string movieId;
    string title;

public:
    Movie(string id, string t)
        : movieId(id), title(t) {}

    string getTitle() { return title; }
};

// ---------------- SHOW ---------------- 

class Show {
private:
    string showId;
    Movie* movie;
    Screen* screen;
    unordered_map<string, Seat*> seatMap;

public:
    Show(string id, Movie* m, Screen* s)
        : showId(id), movie(m), screen(s) {

        for (auto seat : s->getSeats()) {
            seatMap[seat->getId()] = seat;
        }
    }

    bool lockSeat(string seatId) {
        if (seatMap.count(seatId) &&
            seatMap[seatId]->lockSeat()) {
            return true;
        }
        return false;
    }

    vector<Seat*> getSeats(vector<string> ids) {
        vector<Seat*> res;
        for (auto& id : ids) {
            if (seatMap.count(id))
                res.push_back(seatMap[id]);
        }
        return res;
    }

    void displaySeats() {
        cout << "\nSeat Status:\n";
        for (auto& [id, seat] : seatMap) {
            cout << id << " -> ";
            if (seat->getStatus() == SeatStatus::AVAILABLE)
                cout << "AVAILABLE\n";
            else if (seat->getStatus() == SeatStatus::LOCKED)
                cout << "LOCKED\n";
            else
                cout << "BOOKED\n";
        }
    }
};

// ---------------- PAYMENT STRATEGY ---------------- 

class Payment {
public:
    virtual bool pay(double amount) = 0;
};

class UpiPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Payment successful via UPI: ₹"
             << amount << endl;
        return true;
    }
};

// ---------------- BOOKING ---------------- 

class Booking {
private:
    string bookingId;
    vector<Seat*> seats;
    PaymentStatus status;

public:
    Booking(string id, vector<Seat*> s)
        : bookingId(id), seats(s),
          status(PaymentStatus::PENDING) {}

    void confirmBooking() {
        for (auto seat : seats) {
            seat->bookSeat();
        }
        status = PaymentStatus::SUCCESS;
    }
};

// ---------------- BOOKING SERVICE ---------------- 

class BookingService {
public:
    Booking* createBooking(
        string bookingId,
        Show* show,
        vector<string> seatIds
    ) {
        vector<Seat*> lockedSeats;

        for (auto& id : seatIds) {
            if (show->lockSeat(id)) {
                cout << "Seat locked: " << id << endl;
                lockedSeats.push_back(
                    show->getSeats({id})[0]
                );
            } else {
                throw runtime_error(
                    "Seat not available: " + id
                );
            }
        }

        return new Booking(bookingId, lockedSeats);
    }
};

// ---------------- MAIN (SIMULATION) ---------------- 

int main() {

    // Create Movie
    Movie* movie =
        new Movie("M1", "Interstellar");

    // Create Screen & Seats
    Screen* screen =
        new Screen("Screen1");

    for (int i = 1; i <= 5; i++) {
        screen->addSeat(
            new Seat("S" + to_string(i),
                     SeatType::NORMAL));
    }

    // Create Show
    Show* show =
        new Show("Show1", movie, screen);

    show->displaySeats();

    // Booking Flow
    BookingService service;

    vector<string> seatsToBook = {"S1", "S2"};

    try {
        Booking* booking =
            service.createBooking(
                "B1", show, seatsToBook);

        // Payment
        Payment* payment =
            new UpiPayment();

        if (payment->pay(500)) {
            booking->confirmBooking();
            cout << "Booking Confirmed\n";
        }

    } catch (exception& e) {
        cout << e.what() << endl;
    }

    show->displaySeats();

    return 0;
}
*/