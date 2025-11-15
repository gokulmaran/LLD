/*        ┌────────────────────────┐
          │   AbstractFactory      │
          ├────────────────────────┤
          │ + createShape()        │
          │ + createColor()        │
          └────────────────────────┘
                 ▲                ▲
     ┌────────────┘                └────────────┐
┌──────────────┐                   ┌──────────────┐
│ ShapeFactory │                   │ ColorFactory │
└──────────────┘                   └──────────────┘
client-->abstractfactories
           \\
           Concrete factories--> abstract class-->abstract interface
*/

#include <iostream>
using namespace std;

//Abstract classes
class Button{
  public: 
     virtual void draw()=0;
};

class checkbox{
  public:
     virtual void draw()=0;
};
//concrete classes
class LightButton:public Button{
  public:
     void draw(){
       cout<<"drwing lightButton"<<endl;
     }
};
class Darkbutton: public Button{
  public:
     void draw(){
       cout<<"drawing darkbutton"<<endl;
     }
};
class Lightcheckbox:public checkbox{
  public:
     void draw(){
       cout<<"drwing lightCheckbox"<<endl;
     }
};
class Darkcheckbox: public checkbox{
  public:
     void draw(){
       cout<<"drawing darkCheckbox"<<endl;
     }
};
//Abstract factory
class GUIFactory{
  public:
  virtual Button*createButton()=0;
  virtual checkbox*createcheckbox()=0;
};
//concrete factory
class LightFactory: public GUIFactory{
  public:
     Button*createButton(){
       return new LightButton();
     }
     checkbox*createcheckbox(){
       return new Lightcheckbox();
     }
};
class DarkFactory: public GUIFactory{
  public:
     Button*createButton(){
       return new Darkbutton();
     }
     checkbox*createcheckbox(){
       return new Darkcheckbox();
     }
};
int main() 
{
    GUIFactory*light=new LightFactory();
    DarkFactory*dark=new DarkFactory();
    
    Button*btn=light->createButton();
    checkbox*chkbox=light->createcheckbox();
    btn->draw();
    chkbox->draw();
    
     Button*btnd=dark->createButton();
    checkbox*chkboxd=dark->createcheckbox();
    btnd->draw();
    chkboxd->draw();
    return 0;
}