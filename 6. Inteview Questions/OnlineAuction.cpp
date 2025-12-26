#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* =========================
   Mediator Interface
   ========================= */
class Bidder;  // forward declaration

class AuctionMediator {
public:
    virtual void registerBidder(Bidder* bidder) = 0;
    virtual void placeBid(Bidder* bidder, double amount) = 0;
    virtual void closeAuction() = 0;
    virtual ~AuctionMediator() = default;
};

/* =========================
   Colleague Interface
   ========================= */
class Bidder {
protected:
    string name;
    AuctionMediator* mediator;

public:
    Bidder(string name, AuctionMediator* mediator)
        : name(name), mediator(mediator) {}

    string getName() { return name; }

    virtual void placeBid(double amount) = 0;
    virtual void notify(double amount) = 0;
    virtual ~Bidder() = default;
};

/* =========================
   Concrete Mediator
   ========================= */
class AuctionHouse : public AuctionMediator {
private:
    vector<Bidder*> bidders;
    double highestBid;
    Bidder* highestBidder;
    string item;

public:
    AuctionHouse(string item, double startingPrice)
        : item(item), highestBid(startingPrice), highestBidder(nullptr) {
        cout << "Auction started for " << item
             << " with starting price $" << startingPrice << endl;
    }

    void registerBidder(Bidder* bidder) override {
        bidders.push_back(bidder);
        cout << bidder->getName() << " joined the auction\n";
    }

    void placeBid(Bidder* bidder, double amount) override {
        if (amount <= highestBid) {
            cout << bidder->getName()
                 << " bid $" << amount
                 << " rejected (Current: $" << highestBid << ")\n";
            return;
        }

        highestBid = amount;
        highestBidder = bidder;

        cout << "\n✔ New highest bid: $" << amount
             << " by " << bidder->getName() << endl;

        for (auto b : bidders) {
            if (b != bidder) {
                b->notify(amount);
            }
        }
    }

    void closeAuction() override {
        cout << "\n=== Auction Closed ===\n";
        if (highestBidder) {
            cout << "Winner: " << highestBidder->getName()
                 << " with $" << highestBid << endl;
        } else {
            cout << "No bids placed\n";
        }
    }
};

/* =========================
   Concrete Colleague
   ========================= */
class ConcreteBidder : public Bidder {
public:
    ConcreteBidder(string name, AuctionMediator* mediator)
        : Bidder(name, mediator) {
        mediator->registerBidder(this);
    }

    void placeBid(double amount) override {
        cout << "\n" << name << " placing bid $" << amount << endl;
        mediator->placeBid(this, amount);
    }

    void notify(double amount) override {
        cout << name << " notified: New bid is $" << amount << endl;
    }
};

/* =========================
   Client
   ========================= */
int main() {
    cout << "====== Mediator Pattern: Online Auction ======\n\n";

    AuctionMediator* auction =
        new AuctionHouse("Vintage Guitar", 100);

    Bidder* alice = new ConcreteBidder("Alice", auction);
    Bidder* bob = new ConcreteBidder("Bob", auction);
    Bidder* charlie = new ConcreteBidder("Charlie", auction);

    alice->placeBid(150);
    bob->placeBid(250);
    charlie->placeBid(300);
    alice->placeBid(200);   // rejected
    bob->placeBid(500);     // winner

    auction->closeAuction();

    delete alice;
    delete bob;
    delete charlie;
    delete auction;

    return 0;
}
