#include <iostream>
using namespace std;
/*
Client--> Receiver-->Command Interface(Concrete commands)--> Invoker
*/
//Receiver
class Light{
  public:
     void on(){
       cout<<"Light is on"<<endl;
     }
     void off(){
       cout<<"Light is off"<<endl;
     }
};
//Command Interface
class LightCommand{
    public:
       virtual void execute()=0;
};
///concrete commanders
class LightOn:public LightCommand{
  public:
     Light*l;
    LightOn(Light* light) : l(light) {}
     
     void execute(){
       l->on();
     }
};
class LightOff:public LightCommand{
  public:
     Light*l;
      LightOff(Light* light) : l(light) {}
     
     void execute(){
       l->off();
     }
};
//Invoker
class RemoteControl{
  public:
       LightCommand*lc;
       void setCommand(LightCommand*c){
          lc=c;
       }
       void pressButton(){
         if(lc){
           lc->execute();
         }
       }
};
int main() {
    Light lamp;

    LightOn lightOnCmd(&lamp);    // ✔ pass receiver
    LightOff lightOffCmd(&lamp);  // ✔ pass receiver

    RemoteControl rc;

    rc.setCommand(&lightOnCmd);
    rc.pressButton();  // Light ON

    rc.setCommand(&lightOffCmd);
    rc.pressButton();  // Light OFF

    return 0;
}