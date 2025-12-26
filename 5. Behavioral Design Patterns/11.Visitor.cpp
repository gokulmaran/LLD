#include <iostream>
using namespace std;

/* =========================
   Visitor Interface
   ========================= */
class Book;
class Electronics;

class Visitor {
public:
    virtual void visit(Book* book) = 0;
    virtual void visit(Electronics* electronics) = 0;
    virtual ~Visitor() = default;
};

/* =========================
   Element Interface
   ========================= */
class Item {
public:
    virtual void accept(Visitor* visitor) = 0;
    virtual ~Item() = default;
};

/* =========================
   Concrete Elements
   ========================= */
class Book : public Item {
private:
    int price;

public:
    Book(int price) : price(price) {}

    int getPrice() { return price; }

    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

class Electronics : public Item {
private:
    int price;

public:
    Electronics(int price) : price(price) {}

    int getPrice() { return price; }

    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }
};

/* =========================
   Concrete Visitor
   ========================= */
class PriceCalculator : public Visitor {
private:
    int total = 0;

public:
    void visit(Book* book) override {
        cout << "Book price: " << book->getPrice() << endl;
        total += book->getPrice();
    }

    void visit(Electronics* electronics) override {
        cout << "Electronics price: " << electronics->getPrice() << endl;
        total += electronics->getPrice();
    }

    int getTotal() {
        return total;
    }
};

/* =========================
   Client
   ========================= */
int main() {
    Item* items[] = {
        new Book(200),
        new Electronics(1500),
        new Book(300)
    };

    Visitor* visitor = new PriceCalculator();

    for (auto item : items) {
        item->accept(visitor);
    }

    cout << "-----------------------\n";
    cout << "Total Price = " 
         << static_cast<PriceCalculator*>(visitor)->getTotal()
         << endl;

    // Cleanup
    for (auto item : items) delete item;
    delete visitor;

    return 0;
}
