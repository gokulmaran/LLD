/*
   base class interface-->concrete class  
      |--- -decorator-->concrete decorator
   
*/
#include<iostream>
using namespace std;

//base class
class IceCream{
  public:
      virtual string getDescription()=0;
      virtual double cost()=0;
      virtual ~IceCream() {};
};

//concrete class interface
class VanillaIce: public IceCream{
    public:
       string  getDescription() {
         return "Its vanilla icecream ";
       }
       double cost() {
          return 50.0;
       }
};

//decorator abstract class
class iceDecorator: public IceCream{
    public:
        IceCream *icecream;
        iceDecorator(IceCream *ic){
          icecream=ic;
        }
        string getDescription() {
           return icecream->getDescription();
        }
        double cost() {
          return icecream->cost();
        }
};

//chocolate decorator
class chocolateDecorator: public iceDecorator{
    public:
         chocolateDecorator(IceCream* ic) : iceDecorator(ic) {
        // Correct way to initialize base class pointer by calling base constructor
    }
          string getDescription () {
           return icecream->getDescription()+"with chocolate";
        }
        double cost() {
         return icecream->cost()+60.0;
        }
};

int main(){
    IceCream*Vanilla=new VanillaIce();
    cout<<Vanilla->getDescription()<<endl;
     cout<<Vanilla->cost()<<endl;

    IceCream*chocoDecorator=new chocolateDecorator(Vanilla);
     cout<< chocoDecorator->getDescription()<<endl;
    cout<< chocoDecorator->cost()<<endl;
   delete chocoDecorator;
    delete Vanilla;
}
