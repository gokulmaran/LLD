#include <iostream>
#include <vector>
using namespace std;

/* =========================
   Element
   ========================= */
class Book {
    string title;
public:
    Book(string t) : title(t) {}

    string getTitle() const {
        return title;
    }
};

/* =========================
   Iterator Interface
   ========================= */
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual Book next() = 0;
    virtual ~Iterator() {}
};

/* =========================
   Aggregate Interface
   ========================= */
class Aggregate {
public:
    virtual Iterator* createIterator() = 0;
    virtual ~Aggregate() {}
};

/* =========================
   ConcreteAggregate
   ========================= */
class Library : public Aggregate {
    vector<Book> books;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    // Creates iterator (as shown in diagram)
    Iterator* createIterator() override;
    
    vector<Book>& getBooks() {
        return books;
    }
};

/* =========================
   ConcreteIterator
   ========================= */
class BookIterator : public Iterator {
    vector<Book>& books;
    int index = 0;

public:
    BookIterator(vector<Book>& b) : books(b) {}

    bool hasNext() override {
        return index < books.size();
    }

    Book next() override {
        return books[index++];
    }
};

/* =========================
   Iterator Creation
   ========================= */
Iterator* Library::createIterator() {
    return new BookIterator(books);
}

/* =========================
   Client
   ========================= */
int main() {
    Library library;

    library.addBook(Book("Clean Code"));
    library.addBook(Book("Design Patterns"));
    library.addBook(Book("Refactoring"));

    Iterator* it = library.createIterator();

    cout << "Books in Library:\n";
    while (it->hasNext()) {
        Book b = it->next();
        cout << "- " << b.getTitle() << endl;
    }

    delete it;
    return 0;
}
