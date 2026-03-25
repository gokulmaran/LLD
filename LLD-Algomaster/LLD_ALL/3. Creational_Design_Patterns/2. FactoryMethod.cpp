/* 
    client--> factory -->interface-->concrete classes
    2. Factory Method
Real world example
Consider the case of a hiring manager. It is impossible for one person to
interview for each of the positions. Based on the job opening, she has to decide and
delegate the interview steps to different people.

In plain words
It provides a way to delegate the instantiation logic to child classes.

Wikipedia says
In class-based programming, the factory method pattern is a creational
pattern that uses factory methods to deal with the problem of creating objects
without having to specify the exact class of the object that will be created. This is
done by creating objects by calling a factory method—either specified in an interface
and implemented by child classes, or implemented in a base class and optionally
overridden by derived classes—rather than by calling a constructor.

Programmatic Example
Taking our hiring manager example above. First of all we have an interviewer
interface and some implementations for it
*/

#include <iostream>
using namespace std;

class Shape{
  public:
       virtual void draw()=0;
};
//concrete classes
class Circle: public Shape{
  public: 
       void draw(){
         cout<<"Drawing a Circle shape\n";
       }
};
class Square: public Shape{
  public:
        void draw(){
          cout<<"Drawing a square shape\n";
        }
};
//Now let us create our Shapefactory, any shape can call
class ShapeFactory{
  public:
    static Shape*getShape(string type){
        if(type=="circle"){
           return new Circle();
        }
        else {
           return new Square();
        }
    }
};
int main() 
{
    Shape*s1= ShapeFactory::getShape("circle");
    Shape*s2=ShapeFactory::getShape("square");
    
    s1->draw();
    s2->draw();
}
