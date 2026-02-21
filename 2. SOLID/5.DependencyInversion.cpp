#include <iostream>
using namespace std;

//abstraction
class Switchable{
    public:
      virtual void turnOn()=0;
      virtual void turnOff()=0;
};
class LightBulb: public Switchable{
  public:
     void turnOn(){
         cout<<"LightBulb turning ON"<<endl;
     }
     void turnOff(){
         cout<<"LightBulb turning Off"<<endl;
     }
};

class LED: public Switchable{
  public:
     void turnOn(){
         cout<<"LED turning ON"<<endl;
     }
     void turnOff(){
         cout<<"LED turning Off"<<endl;
     }
};
class LightSwitch{
  public:
    Switchable*s;
    bool isOn=false;
    
    LightSwitch(Switchable*s):s(s){}
    
    void toggle(){
        if(isOn){
            s->turnOff();
            isOn=false;
        }
        else{
            s->turnOn();
            isOn=true;
        }
    }
};
int main(){
   LightBulb bulb;
   LightSwitch l(&bulb);
   
   l.toggle();
   
}