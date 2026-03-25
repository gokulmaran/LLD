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
using namespace std;

/*
client-->target-->Adaptee->adapter
*/
//target
class UpiPayment{
  public:
     virtual void payUsingUPI(int amt)=0;
};

//adaptee
class PayPal{
  public:
    void sendMoney(int amt){
      cout<<"Sending money"<<" Rs."<<amt<<endl;
    }
};
//adapter
class PayPalAdapter: public UpiPayment{
   public:
     PayPal*pay;
     PayPalAdapter(PayPal* pp) {
        pay = pp;
    }
      void payUsingUPI(int amt){
         cout<<"adapter makes send pay call.. "<<endl;
         pay->sendMoney(amt);
     }
};
int main() 
{
    PayPal pay;
    PayPalAdapter adapter(&pay);
    adapter.payUsingUPI(100);
    return 0;
}
