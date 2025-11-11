/*

Client--> Facade class-> Sub classess 1, Sub classes 2
                              
*/


#include <iostream>
using namespace std;

//Option Chain
class Engine{
  public:
     void start(){
       cout<<"start on engine"<<endl;
     }
};

class Light{
  public:
     void turnOn(){
       cout<<"Lights On"<<endl;
     }
};

class Car{
  public:
   Engine engine;
   Light light;
   
   void carIgnition(){
     engine.start();
     light.turnOn();
   }
};
int main() 
{
    Car car;
    car.carIgnition();
  
}