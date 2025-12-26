#include <iostream>
using namespace std;

/* =========================
   Abstract Class
   ========================= */
class PaymentFlow {
public:
    // Abstract steps
    virtual void validateRequest() = 0;
    virtual void debitAmount() = 0;
    virtual void calculateFees() = 0;
    virtual void creditAmount() = 0;

    // Template Method (defines algorithm order)
    void sendMoney() {
        validateRequest();   // Step 1
        debitAmount();       // Step 2
        calculateFees();     // Step 3
        creditAmount();      // Step 4
    }

    // Hook Method (optional override)
    virtual bool requiresOTPAuthentication() {
        return false;  // Default behavior
    }

    // Common method
    void logTransaction() {
        cout << "Transaction Completed!" << endl;
    }

    virtual ~PaymentFlow() {}
};

/* =========================
   Concrete Class: Bank Transfer
   ========================= */
class BankTransfer : public PaymentFlow {
public:
    void validateRequest() override {
        cout << "[+] Specific Validation Logic for Bank Transfer" << endl;
    }

    void debitAmount() override {
        cout << "[+] Specific Debit Amount Logic for Bank Transfer" << endl;
    }

    void calculateFees() override {
        cout << "[+] Specific Fee Calculation Logic for Bank Transfer. 0% Fees is applied." << endl;
    }

    void creditAmount() override {
        cout << "[+] Specific Credit Amount Logic for Bank Transfer. Full amount is credited." << endl;
    }
};

/* =========================
   Concrete Class: Merchant Payment
   ========================= */
class MerchantPayment : public PaymentFlow {
public:
    void validateRequest() override {
        cout << "[+] Specific Validation Logic for Merchant Payment" << endl;
    }

    void debitAmount() override {
        if (requiresOTPAuthentication()) {
            cout << "[+] Perform OTP Authentication." << endl;
        }
        cout << "[+] Specific Debit Amount Logic for Merchant Payment" << endl;
    }

    void calculateFees() override {
        cout << "[+] Specific Fee Calculation Logic for Merchant Payment. 2% Fees is applied." << endl;
    }

    void creditAmount() override {
        cout << "[+] Specific Credit Amount Logic for Merchant Payment. Remaining amount is credited." << endl;
    }

protected:
    // Hook method overridden
    bool requiresOTPAuthentication() override {
        return true;
    }
};

/* =========================
   Client Code
   ========================= */
int main() {
    cout << "###### Template Method Design Pattern ######\n\n";

    cout << "===== Bank Transfer =====" << endl;
    PaymentFlow* bankTransfer = new BankTransfer();
    bankTransfer->sendMoney();
    bankTransfer->logTransaction();

    cout << "\n===== Merchant Payment =====" << endl;
    PaymentFlow* merchantPayment = new MerchantPayment();
    merchantPayment->sendMoney();
    merchantPayment->logTransaction();

    delete bankTransfer;
    delete merchantPayment;

    return 0;
}
