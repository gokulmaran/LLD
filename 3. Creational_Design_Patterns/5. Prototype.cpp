#include <iostream>
using namespace std;

/* =========================
   Prototype Interface
   ========================= */
class Document {
public:
    virtual Document* clone() = 0;
    virtual void show() = 0;
    virtual ~Document() {}
};

/* =========================
   Concrete Prototype
   ========================= */
class Report : public Document {
private:
    string content;

public:
    Report(string text) : content(text) {}

    // Clone using copy constructor
    Document* clone() override {
        return new Report(*this);
    }

    void show() override {
        cout << "Report Content: " << content << endl;
    }
};

/* =========================
   Client
   ========================= */
int main() {
    cout << "###### Prototype Pattern ######\n\n";

    // Original object
    Document* original = new Report("Annual Sales Report");

    // Clone object
    Document* copy = original->clone();

    original->show();
    copy->show();

    delete original;
    delete copy;

    return 0;
}
