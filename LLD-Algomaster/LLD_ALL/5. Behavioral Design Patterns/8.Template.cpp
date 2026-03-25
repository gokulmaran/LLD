#include<bits/stdc++.h>
using namespace std;
//Template pattern
class Beverage{
  public: 
     void prepareReceipe(){
         brew();
         pourIncup();
         boilWater();
         addCondiments();
     }

     void boilWater(){
         cout<<"boiled water"<<endl;
     }
     void pourIncup(){
         cout<<"poured into cup"<<endl;
     }
     virtual void brew()=0;
     virtual void addCondiments()=0;
};
class Tea:public Beverage{
    public:
      void brew(){
          cout<<"tead can be brewed"<<endl;
      }
      void addCondiments(){
          cout<<"added condiments"<<endl;
      }
};
class Coffee: public Beverage{
  public:
    void brew(){
        cout<<"coffeee can be brewed"<<endl;
    }
     void addCondiments(){
          cout<<"added condiments"<<endl;
      }
};
int main(){
    Tea tea;
    tea.prepareReceipe();
}
