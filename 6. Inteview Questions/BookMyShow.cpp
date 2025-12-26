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
