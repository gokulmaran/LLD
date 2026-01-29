#include <bits/stdc++.h>
using namespace std;

/* =========================
   Enums
   ========================= */
enum class PaymentStatus {
    INITIATED,
    SUCCESS,
    FAILED,
    REFUNDED
};

enum class PaymentMode {
    CARD,
    UPI,
    WALLET
};

/* =========================
   Payment Request / Response
   ========================= */
struct PaymentRequest {
    string paymentId;
    double amount;
    PaymentMode mode;
};

struct PaymentResponse {
    PaymentStatus status;
    string message;
};

/* =========================
   Payment Gateway (Strategy)
   ========================= */
class PaymentGateway {
public:
    virtual PaymentResponse process(double amount) = 0;
    virtual ~PaymentGateway() {}
};

/* =========================
   Concrete Gateways
   ========================= */
class CardPaymentGateway : public PaymentGateway {
public:
    PaymentResponse process(double amount) override {
        return {PaymentStatus::SUCCESS, "Card payment successful"};
    }
};

class UpiPaymentGateway : public PaymentGateway {
public:
    PaymentResponse process(double amount) override {
        return {PaymentStatus::SUCCESS, "UPI payment successful"};
    }
};

class WalletPaymentGateway : public PaymentGateway {
public:
    PaymentResponse process(double amount) override {
        return {PaymentStatus::FAILED, "Wallet balance insufficient"};
    }
};

/* =========================
   Payment Factory
   ========================= */
class PaymentGatewayFactory {
public:
    static unique_ptr<PaymentGateway> getGateway(PaymentMode mode) {
        switch (mode) {
            case PaymentMode::CARD:
                return make_unique<CardPaymentGateway>();
            case PaymentMode::UPI:
                return make_unique<UpiPaymentGateway>();
            case PaymentMode::WALLET:
                return make_unique<WalletPaymentGateway>();
            default:
                return nullptr;
        }
    }
};

/* =========================
   Payment Service
   ========================= */
class PaymentService {
private:
    unordered_map<string, PaymentStatus> paymentStore;
    mutex mtx;

public:
    PaymentResponse makePayment(const PaymentRequest& request) {
        lock_guard<mutex> lock(mtx);

        // Idempotency check
        if (paymentStore.count(request.paymentId)) {
            return {paymentStore[request.paymentId],
                    "Duplicate payment request"};
        }

        auto gateway = PaymentGatewayFactory::getGateway(request.mode);
        PaymentResponse response = gateway->process(request.amount);

        paymentStore[request.paymentId] = response.status;
        return response;
    }

    PaymentResponse refundPayment(const string& paymentId) {
        lock_guard<mutex> lock(mtx);

        if (!paymentStore.count(paymentId)) {
            return {PaymentStatus::FAILED, "Payment not found"};
        }

        paymentStore[paymentId] = PaymentStatus::REFUNDED;
        return {PaymentStatus::REFUNDED, "Refund successful"};
    }
};

/* =========================
   Payment Controller
   ========================= */
class PaymentController {
private:
    PaymentService paymentService;

public:
    PaymentResponse initiatePayment(const PaymentRequest& request) {
        return paymentService.makePayment(request);
    }

    PaymentResponse refund(const string& paymentId) {
        return paymentService.refundPayment(paymentId);
    }
};

/* =========================
   Main (Demo)
   ========================= */
int main() {
    PaymentController controller;

    PaymentRequest req1 = {"PAY123", 1000.0, PaymentMode::CARD};
    PaymentRequest req2 = {"PAY124", 500.0, PaymentMode::WALLET};

    auto res1 = controller.initiatePayment(req1);
    cout << res1.message << endl;

    auto res2 = controller.initiatePayment(req2);
    cout << res2.message << endl;

    auto refundRes = controller.refund("PAY123");
    cout << refundRes.message << endl;

    return 0;
}
