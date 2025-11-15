/*
             ┌──────────────────┐
             │   Color (Implementor) │
             │ + applyColor()        │
             └────────▲───────────┘
                      │
      ┌──────────────────────────────┐
      │                              │
┌──────────────┐             ┌──────────────┐
│ RedColor     │             │ BlueColor    │
│ + applyColor()│            │ + applyColor()│
└──────────────┘             └──────────────┘

             ┌─────────────────────┐
             │ Shape (Abstraction) │
             │ + drawShape()       │
             │ - color: Color*     │
             └────────▲────────────┘
                      │
      ┌──────────────────────────────┐
      │                              │
┌──────────────┐             ┌──────────────┐
│ Circle       │             │ Square       │
│ + drawShape()│             │ + drawShape()│
└──────────────┘             └──────────────┘
*/
//Decouples abstraction from implementation
#include <iostream>
using namespace std;
/*Client--> Abstract class ----->abstract Implemtator-->concrete implementors
             |-> refined abstractions
             
*/
//Implementor
class Color{
  public:
      virtual void applyColor()=0;
};
//Concrete Implementors
class RedColor:public Color{
   public:
      void applyColor(){
        cout<<" Applying Red color"<<endl;
      }
};
class BlueColor:public Color{
   public:
      void applyColor(){
        cout<< " Applying Blue color"<<endl;
      }
};
//Abstract class
class Shape{
  public:
    Color*color; //Bridge
    Shape(Color*c){
      color=c;
    }
    virtual void draw()=0;
};
//concrete abstractors
class Circle:public Shape{
  public:
      Circle(Color*c):Shape(c){};
      void draw(){
        cout<<"Drawing a Circle shape with";
        color->applyColor();
        cout<<endl;
      }
};
class Square:public Shape{
  public:
      Square(Color*c):Shape(c){};
      void draw(){
        cout<<"Drawing a Square shape with";
        color->applyColor();
        cout<<endl;
      }
};
int main() 
{
    Color*red=new RedColor();
    Color*Blue=new BlueColor();
    
    Shape*circle=new Circle(red);
    Shape*square=new Square(Blue);
    
    circle->draw();
    square->draw();
    return 0;
}