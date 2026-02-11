#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// 1. Observer Interface
class IBidder {
public:
    virtual ~IBidder() {}
    virtual void update(std::string auctionName, double newBid, std::string winner) = 0;
    virtual std::string getName() = 0;
};

// 2. Concrete Observer
class Bidder : public IBidder {
private:
    std::string name;
public:
    Bidder(std::string n) : name(n) {}
    std::string getName() override { return name; }
    
    void update(std::string auctionName, double newBid, std::string winner) override {
        if (winner == name) {
            std::cout << "[Notification for " << name << "] You are the current highest bidder for " << auctionName << " at $" << newBid << "!\n";
        } else {
            std::cout << "[Notification for " << name << "] You've been outbid for " << auctionName << ". New high: $" << newBid << " by " << winner << ".\n";
        }
    }
};

// 3. Observable (Subject)
class AuctionListing {
private:
    std::string itemName;
    double currentHighestBid;
    IBidder* currentWinner;
    std::vector<IBidder*> bidders;
    bool isActive;

public:
    AuctionListing(std::string name, double startPrice) 
        : itemName(name), currentHighestBid(startPrice), currentWinner(nullptr), isActive(true) {}

    void registerBidder(IBidder* bidder) {
        bidders.push_back(bidder);
    }

    void placeBid(IBidder* bidder, double bidAmount) {
        if (!isActive) {
            std::cout << "Auction for " << itemName << " is closed.\n";
            return;
        }
        if (bidAmount > currentHighestBid) {
            currentHighestBid = bidAmount;
            currentWinner = bidder;
            notifyBidders();
        } else {
            std::cout << "Bid of $" << bidAmount << " rejected. Must be > $" << currentHighestBid << ".\n";
        }
    }

    void notifyBidders() {
        for (auto bidder : bidders) {
            bidder->update(itemName, currentHighestBid, currentWinner->getName());
        }
    }

    void closeAuction() {
        isActive = false;
        std::cout << "\n--- Auction Closed for " << itemName << " ---\n";
        if (currentWinner) 
            std::cout << "WINNER: " << currentWinner->getName() << " with $" << currentHighestBid << "\n";
        else 
            std::cout << "No bids were placed.\n";
    }
};

int main() {
    // Setup
    AuctionListing* laptopAuction = new AuctionListing("MacBook Pro", 1000.0);

    IBidder* alice = new Bidder("Alice");
    IBidder* bob = new Bidder("Bob");
    IBidder* gokul =new Bidder("Gokul");

    laptopAuction->registerBidder(alice);
    laptopAuction->registerBidder(bob);

    // Bidding Flow
    laptopAuction->placeBid(alice, 1100.0);
    laptopAuction->placeBid(gokul,1500.0);
    laptopAuction->placeBid(bob, 1200.0);
    laptopAuction->placeBid(gokul,1000.0);
    laptopAuction->placeBid(alice, 1150.0); // Should fail
    

    laptopAuction->closeAuction();

    // Cleanup
    delete alice; delete bob;
    delete laptopAuction;

    return 0;
}
