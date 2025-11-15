#include <bits/stdc++.h>
using namespace std;
/*
   interface (observer)-->concrete observer-->Subject class
*/
//observer interface
class Observers{
  public:
      virtual void update(int newValue)=0;
};

//concrete observer
class ConcreteObserver: public Observers{
  public:
     string name;
     ConcreteObserver(string n):name(n){};
     
     void update(int n){
        cout<<"Observers values: "<<n<<endl;
     }
};
//Subject
class Subject{
   public:
      int value=0;
      vector<Observers*>observer;
      
      void attach(Observers*obs){
        observer.push_back(obs);
      }
      void setValue(int v){
        value=v;
        for(Observers*obs:observer){
          obs->update(value);
        }
      }
      
};
int main() 
{
   Subject sub;
   ConcreteObserver c1("A");
   ConcreteObserver c2("B");
   
   sub.attach(&c1);
   sub.attach(&c2);
   
   sub.setValue(10);
   sub.setValue(20);
}