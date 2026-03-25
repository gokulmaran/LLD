#include <iostream>
using namespace std;

/*
 Strategy interface-->concrete strategies--> context
*/
//strategy interface
class Strategy{
  public:
     virtual int execute(int a,int b)=0;
};
//concrete strategies--
class AddStrategy: public Strategy{
  public:
      int execute(int a,int b){
        return a+b;
      }
};
class MultiplyStrategy: public Strategy{
  public:
     int execute(int a,int b){
       return a*b;
     }
};
//context
class Context{
  public:
    Strategy*strategy;
    Context(Strategy*s=nullptr): strategy(s){};
    
    void setStrategy(Strategy*s){
      strategy=s;
    }
    
    int doOperation(int a,int b){
       return strategy->execute(a,b);
    }
};
int main() 
{
    AddStrategy add;
    MultiplyStrategy mul;
    
    Context c;
    c.setStrategy(&add);
    cout<<c.doOperation(3,4)<<endl;
    
    c.setStrategy(&mul);
    cout<<c.doOperation(3,4);
    return 0;
}