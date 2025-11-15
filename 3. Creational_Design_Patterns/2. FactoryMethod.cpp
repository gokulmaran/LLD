/* 
    client--> factory -->interface-->concrete classes
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
