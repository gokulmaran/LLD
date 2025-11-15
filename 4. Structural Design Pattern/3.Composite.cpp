/*
                 ┌──────────────────┐
                 │   Shape           │  ← Abstract Component
                 │ + draw()          │
                 └─────────▲────────┘
                           │
       ┌───────────────────┴────────────────────┐
       │                                        │
┌──────────────┐                     ┌────────────────────┐
│   Circle     │                     │  CompositeShape    │
│ + draw()     │                     │ + add(Shape*)      │
└──────────────┘                     │ + remove(Shape*)   │
                                     │ + draw()           │
                                     └────────────────────┘
*/
//The Composite Pattern lets you treat individual objects and groups of objects uniformly.
#include <bits/stdc++.h>
using namespace std;
/*
Client--> Componeent(leaf1,2)--> Composite 

*/
//Component
class Shape{
  public:
     virtual void draw()=0;
      virtual ~Shape() {};
};
//leaf1
class Circle: public Shape{
    public:
       void draw(){
         cout<<"Drawing a circle"<<endl;
       }
};
//Leaf2
class Square: public Shape{
    public:
       void draw(){
         cout<<"Drawing a square"<<endl;
       }
};
//Composite
class CompositeShape: public Shape{
  public:
     vector<Shape*>children;
     
     void add(Shape*a){
       children.push_back(a);
     }
     void draw(){
       cout<<"Drawing a shapes: ";
       for(auto c:children){
         c->draw();
       }
     }
};
int main() 
{
   Circle c;
   Square s;
   
   CompositeShape comp;
   comp.add(&c);
   comp.add(&s);
    
    comp.draw();
    return 0;
}