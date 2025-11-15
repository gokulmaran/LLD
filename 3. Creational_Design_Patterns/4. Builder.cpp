/*
```
┌─────────────────┐          ┌──────────────────┐          ┌─────────────────┐
│      Pizza      │          │  PizzaBuilder    │          │  PizzaDirector   │
├─────────────────┤          ├──────────────────┤          ├─────────────────┤
│ - dough: string │<>------->│ + setDough()     │          │ + makeHawaiian   │
│ - sauce: string │          │   (string): void │          │   Pizza()        │
│ - topping:      │          │ + setSauce()     │          │   (builder:      │
│   string        │          │   (string): void │          │    PizzaBuilder │
│ + display():    │          │ + setTopping()   │          │   ): void        │
│   void          │          │   (string): void │          └─────────────────┘
└─────────────────┘          │ + getPizza():    │
                             │   Pizza          │
                             └──────────────────┘
                                      ^
                                      |
                             ┌──────────────────┐
                             │HawaiianPizza     │
                             │Builder           │
                             ├──────────────────┤
                             │ - pizza:         │
                             │   Pizza          │
                             ├──────────────────┤
                             │ + setDough()     │
                             │   (string): void │
                             │ + setSauce()     │
                             │   (string): void │
                             │ + setTopping()   │
                             │   (string): void │
                             │ + getPizza():    │
                             │   Pizza          │
                             └──────────────────┘
```
client-->creates a concrete builder and passes to director, and get a Burger
*/
#include <iostream>
using namespace std;

/*
 client--> Product ->builder interface--> director
                      \-->concrete builder
*/

//Product
class Burger{
 public:
     string cheese;
     string tomato;
     string sauce;
     void display(){
       cout<<"Burger with "<<"\n"<<
              "tomato: "<<tomato<<"\n"<<
              "cheese: "<<cheese<<"\n"<<
              "sauce: "<<sauce<<endl;
                   
     }
};

//builder interface--
class BurgerBuilder{
  public:
      virtual void setTomato(string tomato)=0;
      virtual void setCheese(string cheese)=0;
      virtual void setSauce(string sauce)=0;
      virtual Burger getBurger()=0;
      virtual ~BurgerBuilder() {}
};

//concrete builder 
class VegBurger:public BurgerBuilder{
  public:
      Burger burger;
      void setTomato(string tomato){
         burger.tomato=tomato;
      }
      void setCheese(string cheese){
         burger.cheese=cheese;
      }
      void setSauce(string sauce){
         burger.sauce=sauce;
      }
      Burger getBurger(){
        return burger;
      }
};
//director
class BurgerDirector{
  public:
      void makeVegBurger(BurgerBuilder &builder){
          builder.setTomato("redTomato");
          builder.setSauce("redSauce");
          builder.setCheese("redCheese");
      }
};
int main() 
{
    BurgerDirector director;
    VegBurger builder;
    
    director.makeVegBurger(builder);
    
    Burger burger=builder.getBurger();
    burger.display();
    return 0;
}