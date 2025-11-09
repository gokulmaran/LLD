/*
             ┌────────────────────┐
             │ PaymentProcessor    │   ← Target interface
             │ + pay(amount):void │
             └─────────▲──────────┘
                       │
             ┌─────────┴──────────┐
             │ PayPalAdapter      │   ← Adapter
             │ - paypal: PayPal*  │
             │ + pay(amount):void │
             └─────────▲──────────┘
                       │
             ┌─────────┴──────────┐
             │ PayPal             │   ← Adaptee
             │ + sendPayment(sum) │
             └────────────────────┘

             ┌────────────────────┐
             │ Client (main)      │
             │ uses PaymentProcessor │
             └────────────────────┘
*/
//Converts interface of a class into another expected interface
#include <iostream>
#include <string>
using namespace std;

// 🎯 Target Interface
class PaymentProcessor {
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentProcessor() = default;
};

// ⚙️ Adaptee (Existing class with incompatible interface)
class PayPal {
public:
    void sendPayment(double totalAmount) {
        cout << "Processing payment via PayPal: $" << totalAmount << endl;
    }
};

// 🔄 Adapter
class PayPalAdapter : public PaymentProcessor {
    PayPal* paypal;
public:
    PayPalAdapter(PayPal* p) : paypal(p) {}

    void pay(double amount) override {
        cout << "[Adapter] Converting PaymentProcessor request to PayPal format...\n";
        paypal->sendPayment(amount);
    }
};

// 🧠 Client code
int main() {
    PayPal* paypal = new PayPal();
    PaymentProcessor* processor = new PayPalAdapter(paypal);

    processor->pay(250.75);  // Client works with PaymentProcessor interface

    delete processor;
    delete paypal;
    return 0;
}
